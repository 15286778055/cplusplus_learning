#include <iostream>

class Stream {
public:
    virtual char Read(int number) = 0;
    virtual void Seek(int position) = 0;
    virtual void Write(char data) = 0;
};


/* 主体 */
class FileStream : public Stream {
public:
    virtual char Read(int number) override {}
    virtual void Seek(int position) override {}
    virtual void Write(char data) override {}
};

class NetworkStream : public Stream {
public:
    virtual char Read(int number) override {}
    virtual void Seek(int position) override {}
    virtual void Write(char data) override {}
};

class MemoryStream : public Stream {
public:
    virtual char Read(int number) override {}
    virtual void Seek(int position) override {}
    virtual void Write(char data) override {}
};



/* 扩展操作 */
class DecoratorStream : public Stream {
public:
    DecoratorStream(Stream *stm) : stream(stm) {}

protected:
    /* 组合代替继承 */
    Stream *stream;
};

class CryptoStream : public DecoratorStream {
public:
    CryptoStream(Stream *stm) : DecoratorStream(stm) {}

    virtual char Read(int number) override {
        /* 1 Cryto 的特殊功能 */

        /* 2 多态 */
        stream->Read(number);
    }

    virtual void Seek(int position) override {
        /* 1 Cryto 的特殊功能 */
        
        /* 2 多态 */
        stream->Seek(position);
    }

    virtual void Write(char data) override {
        /* 1 Cryto 的特殊功能 */

        /* 2 多态 */
        stream->Write(data);
    }
};

class BufferedStream : public DecoratorStream {
public:
    BufferedStream(Stream *stm) : DecoratorStream(stm) {}

    virtual char Read(int number) override {
        /* 1 Buffered 的特殊功能 */
        
        /* 2 多态 */
        stream->Read(number);
    }

    virtual void Seek(int position) override {
        /* 1 Buffered 的特殊功能 */
        
        /* 2 多态 */
        stream->Seek(position);
    }

    virtual void Write(char data) override {
        /* 1 Buffered 的特殊功能 */
        
        /* 2 多态 */
        stream->Write(data);
    }
};


int main() {

    FileStream *s1 = new FileStream();
    CryptoStream *s2 = new CryptoStream(s1);        /* FileStream主体 + CryptoStream装配 */
    BufferedStream *s3 = new BufferedStream(s1);    /* FileStream主体 + BufferenStream装配 */
    BufferedStream *s4 = new BufferedStream(s2);    /* FileStream主体 + Crypto装配 + Buffered装配 */
    
    

    return 0;
}

