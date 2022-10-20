#include <http_conn.h>

int setnonblocking( int fd )
{

}

void addfd( int epollfd, int fd, bool one_shot )
{

}

void removefd( int epollfd, int fd )
{

}

void modfd( int epollfd, int fd, int ev )
{

}

/* 静态变量初始化 */
int http_conn::m_user_count = 0;
int http_conn::m_epollfd = -1;

void http_conn::close_conn(bool real_close)
{

}

void http_conn::init( int sockfd, const sockaddr_in& addr )
{

}

void http_conn::init()
{

}

http_conn::LINE_STATUS http_conn::parse_line()
{

}

bool http_conn::read()
{

}

http_conn::HTTP_CODE http_conn::parse_request_line( char* text )
{

}

http_conn::HTTP_CODE http_conn::parse_headers( char* text )
{

}

http_conn::HTTP_CODE http_conn::parse_content( char* text )
{

}

http_conn::HTTP_CODE http_conn::process_read()
{

}

http_conn::HTTP_CODE http_conn::do_request()
{

}

void http_conn::unmap()
{

}

bool http_conn::write()
{

}

bool http_conn::add_response( const char* format, ... )
{

}

bool http_conn::add_status_line( int status, const char* title)
{

}

bool http_conn::add_headers( int content_len )
{

}

bool http_conn::add_content_length( int content_len )
{

}

vool http_conn::add_linger()
{

}

bool http_conn::add_blank_line( const char* content)
{

}

bool http_conn::add_content( const char* content)
{

}

bool http_conn::process_write( HTTP_CODE ret )
{

}

void http_conn::process()
{
    
}