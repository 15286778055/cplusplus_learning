#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdip.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cassert>
#include <sys/epoll.h>

#include "locker.h"
#include "threadpool.h"
#include "http_conn.h"

#define MAX_FD 65536
#define MAX_EVENT_NUMBER 10000

extern int addfd( int epollfd, int fd, bool one_shot );
extern int removefd( int epollfd, int fd );

void addsig( int sig, void( hander )(int), bool restart = true)
{
    struct sigaction sa;
    memset( &sa, '\0', sizeof( sa ) );
    sa.sa_handler = handler;
    if (restart)
    {
        sa.sa_flags |= SA_RESTART;
    }
    sigfillset( &sa.sa_mask );
    assert( sigaction( sig, &sa, NULL ) != -1 );
}

void show_error( int connfd, const char* info )
{
    printf( "%s", info );
    send( connfd, info, strlen( info ), 0);
    close( connfd );
}


int main( int argc, char* argv[] )
{
    if ( argc <= 2)
    {
        printf( "usage: %s ip_address port_number\n", basename( argv[0] ) );
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi( argv[2] );

    /* 忽略 SIGPIPE 信号*/
    addsig( SIGPIPE, SIG_IGN );

    /* 创建线程池 */
    threadpool< http_conn>* pool = NULL;
    try
    {
        pool = new threadpool< http_conn >;
    }
    catch ( ... )
    {
        return 1;
    }

    /* 预先为每个可能的客户连接分配一个 http_conn 对象 */
    http_conn* users = new http_conn[ MAX_FD ];
    assert( users );
    int user_count = 0;

    int listenfd = socket( PF_INET, SOCK_STREAM, 0);
    assert( listenfd >= 0 );
    /* 调用 closesocket 之后，立刻返回，不会发送未发送完的数据，而是通过一个 REST 包强制的关闭 socket 描述符，也就是强制退出 */
    struct linger tmp = { 1, 0 };
    setsockopt( listenfd, SOL_SOCKET, SO_LINGER, &tmp, sizeof( tmp ) );

    int ret = 0;
    struct sockaddr_in address;
    bzero( &address, sizeof( address ) );
    address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &address.sin_addr );
    address.sin_port = htons( port );

    ret = bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
    assert( ret >= 0 );

    ret = listen( listenfd, 5 );
    assert( ret >= 0 );

    epoll_event events[ MAX_EVENT_NUMBER ];
    int epollfd = epoll_create( 5 );
    assert( epollfd != -1 );
    addfd( epollfd, listenfd, false );
    http_conn::m_epollfd = epollfd;

    while( true )
    {
        int number = epoll_wait( epollfd, events, MAX_EVENT_NUMBER, -1 );
        if ( ( number < 0) && (errno != EINTR ) )
        {
            printf( "epoll failure\n" );
            break;
        }

        for ( int i = 0; i < number; i++ )
        {
            int sockfd = events[i].data.fd;
            /* 监听 socket */
            if ( sockfd == listenfd )
            {
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof( client_address );
                int connfd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
                if ( connfd < 0)
                {
                    printf( "errno is: %d\n", errno );
                    continue;
                }
                /* 服务人数超过上限 */
                if (http_conn::m_user_count >= MAX_FD )
                {
                    show_error( connfd, "Internal server busy" );\
                    continue;
                }
                /* 初始化 http 服务*/
                /* connfd 对应的 第 connfd-1 个 http 对象 对这个 socket 服务*/
                users[connfd].init( connfd, client_address );
            }
            /* 已连接 socket 的 EPOLLRDHUP EPOLLHUP EPOLLERR */
            else if( events[i].events & ( EPOLLRDHUP | EPOLLHUP | EPOLLERR) )
            {
                users[sockfd].close_conn();
            }
            /* 已连接 socket 的 EPOLLIN */
            else if( events[i].events & EPOLLIN )
            {
                if (users[sockfd].read()
                {
                    /* 将当前 sockfd 对应的 http 对象加入到线程中？？？？不会重复?? */
                    pool->append( users + sockfd );
                }
                else
                {
                    users[sockfd].close_conn();
                }
            }
            /* 已连接 socket 的 EPILLOUT */
            else if ( events[i].events & EPOLLOUT )
            {
                if ( !users[sockfd].write() )
                {
                    users[sockfd].close_conn();
                }
            }
            else
            {}

        }
    }

    close( epollfd );
    close( listenfd );
    delete []users;
    delete pool;
    
    return 0;
}