#ifndef _UTILS_BIN_PACKET_H_
#define _UTILS_BIN_PACKET_H_
#include <arpa/inet.h>	
#include <string>
#include <stdint.h>
#include "type_trait.h"


using namespace std;
namespace CPPSocket
{
	
  typedef struct P_STR{
    P_STR(char *data_,uint32_t len_):len(len_),data(data_){}
    uint32_t len;
    char * data;
  }PSTR;

  typedef struct N_STR{
    N_STR():len(0),data(NULL){}
    uint32_t len;
    char * data;
  }NSTR;

  typedef struct B_STR{
    B_STR():len(0),data(NULL){}
    uint32_t len;
    char * data;
  }BSTR;

  typedef struct BN_STR{
    BN_STR():len(0),data(NULL){}
    uint32_t len;
    char * data;
  }BNSTR;

// D = true ,数据包从左往右  默认方式
//D = false 数据包从右往左

  template <bool D = true>  
  class BinPacket
  {
  	public:
  		BinPacket(char* begin , char* end):m_good(true),m_eof(false),m_begin(begin),
        m_end(end),m_current(begin),m_head_len(0)
  		{
  			if(!D) m_current = m_end;
  		}

  		BinPacket(char* begin , uint32_t len):m_good(true),m_eof(false),m_begin(begin),
        m_end(begin+len),m_current(begin),m_head_len(0)
  		{
  			if(!D) m_current = m_end;
  		}
		
      ~BinPacket(){}
  		
  		uint32_t size() { return (m_end - m_begin) ; }
  		
      void offset(uint32_t len)
  		{
  			if(!m_good) return;
  			if(D){
  				if( m_end - m_current < len ){
  					m_good = false;
  					return;
  				}
  				m_current += len;
  			}else{
  				if(m_current - m_begin < len){
  					m_good = false;
  					return;
  				}
  				m_current -= len;
  			}
  		}
  		
    	void offset_head(uint32_t len)
  		{
  			if(!m_good) return;
  			if(D){ 
  				if( m_end - m_begin < static_cast<int32_t>(len) || m_current != m_begin ){
  					m_good = false;
  					return;
  				}
  				m_head_len = len;
  				m_current += m_head_len;
  			}else{
  				if( m_end - m_begin < static_cast<int32_t>(len) ){
  					m_good = false;
  					return;
  				}
  				m_head_len = len;
  			}
  		}
  		
  		uint32_t remainLength()
  		{
  			if(D) return (m_end - m_current) ;
  			else  return (m_current - m_begin) ;
  		}
  		
    	uint32_t length()
  		{ 
  			if(D) return (m_current - m_begin) ;
  			else  return (m_end - m_current) ;
  		}
  		
  		void rollback()
  		{
  				if(D)
  				{
  						m_current = m_begin + m_head_len;
  				}
  				else
  				{
  						m_current = m_end;
  				}
  		}
  		
    	void clear()
  		{
  			if(D) m_current = m_begin;
  			else m_current = m_end;
  			m_head_len = 0; 
  		}
  		
    	void set_pkglen(uint32_t len)
  		{
  			if(!m_good) return;
  			if(D){
  				if( m_end - m_begin < static_cast<int32_t>(len) || m_current - m_begin > static_cast<int32_t>(len) ){
  					m_good = false;
  					return;
  				}
  				m_end = m_begin + len;
  			}else{
  				if( m_end - m_begin < static_cast<int32_t>(len) || m_end - m_current > static_cast<int32_t>(len) ){
  					m_good = false;
  					return;
  				}
  				m_begin = m_end - len;
  			}
  		}
  		
    	char * getData()
  		{ 
  			if(D) return m_begin ; 
  			else return m_current;
  		}
  		
  		char * getCur()
  		{
  			return m_current;
  		}
  		
  		bool good(){ return m_good; }
  		bool eof(){ return m_eof; }
		
  	public:
  		bool m_good;
  		bool m_eof;
    	char* m_begin;
    	char* m_end;
    	char* m_current;
    	uint32_t m_head_len;
  };

  template<bool D=true>
  class BinInputPacket : public BinPacket<D>
  {
  	public:
  		BinInputPacket(char* begin , char* end):BinPacket<D>( begin , end){}
        BinInputPacket(char* begin , uint32_t len):BinPacket<D>( begin , len){}
  		~BinInputPacket(){}
  		
  		//拆包
  		int read(char * buf, int n = 1)
  		{
  			if( !this->m_good || this->m_eof) return 0;
  			if( n <= 0 ) return 0;
  			if(D){
  				n = (this->m_end - this->m_current) > n ? n : (this->m_end - this->m_current);
  				memcpy(buf, this->m_current , n);
  				this->m_current += n;
  				if( this->m_end == this->m_current ) this->m_eof = true;
  			}else{
  				n = (this->m_current - this->m_begin) > n ? n : (this->m_current - this->m_begin);
  				this->m_current -= n;
  				memcpy(buf, this->m_current , n);
  				if(this->m_current == this->m_begin) this->m_eof = true;
  			}
  			return n;
  		}
  		template<class T> void get_head(T& value)
  		{
  			if(!this->m_good) return ;
  			if( sizeof(T) != this->m_head_len ){
  				this->m_good = false;
  				return;
  			}
  			if(D){
  				value = *reinterpret_cast<T*>(this->m_begin);
  			}else{
  				value = *reinterpret_cast<T*>(this->m_current);
  				this->m_current -= sizeof(T);
  			}
  		}

  		template<class T> friend BinInputPacket& operator>>(BinInputPacket& in, T& value)
  		{
  			if(!in.m_good || in.m_eof) return in;
  			if(D){
  				if(in.m_end - in.m_current < static_cast<int32_t>(sizeof(T))){
  					in.m_good = false;
  					return in;
  				}
  			}else{
  				if(in.m_current - in.m_begin < static_cast<int32_t>(sizeof(T))){
  					in.m_good = false;
  					return in;
  				}
  			}
  			switch(sizeof(T)){
  				case 1:{
  					if(D) value = *reinterpret_cast<T*>(in.m_current++);
  					else value = *reinterpret_cast<T*>(--in.m_current);
  					}break;
  				case 2:{
  					if( TypeTest<T>::IS_SHORT || TypeTest<T>::IS_UNSIGNED_SHORT ){
  						if(D) value = ntohs(*reinterpret_cast<T*>(in.m_current));
  						else value = ntohs(*reinterpret_cast<T*>((in.m_current-2)));
  					}else{
  						if(D) value = *reinterpret_cast<T*>(in.m_current);
  						else value = *reinterpret_cast<T*>((in.m_current-2));
  					}	
  					if(D) in.m_current += 2;
  					else  in.m_current -= 2;
  					}break;
  				case 4:{
  					if( TypeTest<T>::IS_INT || TypeTest<T>::IS_UNSIGNED_INT ){
  						if(D) value = ntohl(*reinterpret_cast<T*>(in.m_current));
  						else  value = ntohl(*reinterpret_cast<T*>((in.m_current-4)));
  					}else{
  						if(D) value = *reinterpret_cast<T*>(in.m_current);
  						else value = *reinterpret_cast<T*>((in.m_current-4));
  					}
  					if(D) in.m_current += 4;
  					else in.m_current -= 4;
  					}break;			
  				default:{
  					if(D) value = *reinterpret_cast<T*>(in.m_current);
  					else value = *reinterpret_cast<T*>((in.m_current - sizeof(T)));
  					
  					if(D) in.m_current += sizeof(T);
  					else in.m_current -= sizeof(T);
  					}break;	
  			}
  			if(D){
  				if(in.m_current == in.m_end) in.m_eof = true;
  			}
  			else{
  				if(in.m_current == in.m_begin) in.m_eof = true;
  			}
  			return in;
  		}

  		friend BinInputPacket& operator>>(BinInputPacket& in, string& value)
  		{
  			if(!in.m_good || in.m_eof) return in;
  		  if(!D) return in;
  			uint32_t len = 0;
  			in>>len;
  			if( in.m_end - in.m_current < len || 2 > len ){
  				in.m_good = false;
  				return in;
  			}
  			char * end =  in.m_current + len - 2;
  			value = string(in.m_current,end);
  			in.m_current += len;
  			if(in.m_current == in.m_end) in.m_eof = true;
  			return in;
  		}

  		friend BinInputPacket& operator>>(BinInputPacket& in, char* value)
  		{
  			if(!in.m_good || in.m_eof) return in;
  		  if(!D) return in;
  		  uint32_t len = 0;
  			in>>len;
  			if( in.m_end - in.m_current < len || 2 > len ){
  				in.m_good = false;
  				return in;
  			}
  			memcpy(value, in.m_current, len);
  			in.m_current += len;
  			if(in.m_current == in.m_end) in.m_eof = true;
  			return in;	
  		}
      
      friend BinInputPacket& operator>>(BinInputPacket& in, PSTR& value)
      {
  			if(!in.m_good || in.m_eof) return in;
  		  if(!D) return in;
        uint32_t len;
  			in>>len;
  			if( in.m_end - in.m_current < static_cast<int32_t>(len) || value.len < len ){
  				in.m_good = false;
  				return in;
  			}
        value.len = len;
  			memcpy(value.data, in.m_current, value.len);
  			in.m_current += len;
  			if(in.m_current == in.m_end) in.m_eof = true;
  			return in;
      }

      friend BinInputPacket& operator>>(BinInputPacket& in, BSTR& value)
      {
  			if( !in.m_good || in.m_eof) return 0;
            int& n = value.len;
  			if( n <= 0 ) return 0;
  			if(D){
  				n = (in.m_end - in.m_current) > n ? n : (in.m_end - in.m_current);
                value.data = in.m_current;
  				in.m_current += n;
  				if( in.m_end == in.m_current ) in.m_eof = true;
  			}else{
  				n = (in.m_current - in.m_begin) > n ? n : (in.m_current - in.m_begin);
  				in.m_current -= n;
                value.data = in.m_current;
  				if(in.m_current == in.m_begin) in.m_eof = true;
  			}
  			return in;
      }

      friend BinInputPacket& operator>>(BinInputPacket& in, NSTR& value)
      {
  			if(!in.m_good || in.m_eof) return in;
  		  if(!D) return in;
        uint32_t len;
  			in>>len;
  			if( in.m_end - in.m_current < static_cast<int32_t>(len) ){
  				in.m_good = false;
  				return in;
  			}
        value.len = len;
        value.data = in.m_current;
  			in.m_current += len;
  			if(in.m_current == in.m_end) in.m_eof = true;
  			return in;
      }

      friend BinInputPacket& operator>>(BinInputPacket& in, BNSTR& value)
      {
  			if(!in.m_good || in.m_eof) return in;
  		  if(!D) return in;
        uint32_t len;
  			in>>len;
  			if( in.m_end - in.m_current < static_cast<int32_t>(len) ){
  				in.m_good = false;
  				return in;
  			}
        value.len = len;
        value.data = in.m_current;
  			in.m_current += len;
  			if(in.m_current == in.m_end) in.m_eof = true;
  			return in;
      }

  };

  template <bool D=true>
  class BinOutputPacket : public BinPacket<D>
  {
  	public:
  		BinOutputPacket(char* begin , char* end):BinPacket<D>( begin , end){}
        BinOutputPacket(char* begin , uint32_t len):BinPacket<D>( begin , len){}
  		~BinOutputPacket(){}
  	
  		// 组包		
  		BinOutputPacket& write(char * buf, int n = 1)
  		{
  			if(!this->m_good || this->m_eof) return *this;
  			if(D){
  				if(n <= 0 || this->m_end - this->m_current < n ){
  					this->m_good = false;
  					return *this;
  				}
  				memcpy(this->m_current, buf, n);
  				this->m_current += n;
  			}else{
  				if(n <= 0 || this->m_current - this->m_begin < n ){
  					this->m_good = false;
  					return *this;
  				}
  				this->m_current -= n;
  				memcpy(this->m_current, buf, n);				
  			}
  			if(this->m_current == this->m_begin) this->m_eof = true;
            return *this;
  		}
		
  		template<class T> void set_head(T value)
  		{
  			if(!this->m_good) return ;
  			if( sizeof(T) != this->m_head_len ){
  				this->m_good = false;
  				return ;
  			}
  			if(D){
  				*reinterpret_cast<T*>(this->m_begin) = value;
  			}else{
  				*reinterpret_cast<T*>(this->m_current - sizeof(T)) = value;
  				this->m_current -= sizeof(T);
  			}
  		}
		
  		template<class T> friend BinOutputPacket& operator<<(BinOutputPacket& out, T value)
  		{
  			if(!out.m_good || out.m_eof) return out;
  			if(D){
  				if(out.m_end - out.m_current < static_cast<int32_t>(sizeof(T))){
  					out.m_good = false;
  					return out;
  				}
  			}else{
  				if(out.m_current - out.m_begin < static_cast<int32_t>(sizeof(T))){
  					out.m_good = false;
  					return out;
  				}
  			}
  			switch(sizeof(T)){
  				case 1:{
  					if(D) *reinterpret_cast<T*>(out.m_current++) = value;
  					else *reinterpret_cast<T*>(--out.m_current) = value;					
  					}break;
  				case 2:{
  					if( TypeTest<T>::IS_SHORT || TypeTest<T>::IS_UNSIGNED_SHORT ){
  						if(D) *reinterpret_cast<T*>(out.m_current) = htons(value);
  						else *reinterpret_cast<T*>((out.m_current-2)) = htons(value);
  					}else{
  						if(D) *reinterpret_cast<T*>(out.m_current) = value;
  						else *reinterpret_cast<T*>((out.m_current-2)) = value;
  					}		
  					if(D) out.m_current += 2;
  					else out.m_current -= 2;
  					}break;
  				case 4:{
  					if( TypeTest<T>::IS_INT || TypeTest<T>::IS_UNSIGNED_INT ){
  						if(D) *reinterpret_cast<T*>(out.m_current) = htonl(value);
  						else *reinterpret_cast<T*>((out.m_current-4)) = htonl(value);
  					}else{
  						if(D) *reinterpret_cast<T*>(out.m_current) = value;
  						else *reinterpret_cast<T*>((out.m_current-4)) = value;
  					}
  					if(D) out.m_current += 4;
  					else out.m_current -= 4;
  					}break;			
  				default:{
  					if(D) *reinterpret_cast<T*>(out.m_current) = value;
  					else *reinterpret_cast<T*>((out.m_current-sizeof(T))) = value;
  					
  					if(D) out.m_current += sizeof(T);
  					else out.m_current -= sizeof(T);
  					}break;	
  			}
  			if(D){
  				if( out.m_current == out.m_end ) out.m_eof = true;
  			}
  			else{
  				if( out.m_current == out.m_begin ) out.m_eof = true;
  			}
  			return out;
  		}
		
  		friend BinOutputPacket& operator<<(BinOutputPacket& out, string value)
  		{
  			if(!out.m_good || out.m_eof) return out;
  		  uint32_t len = value.length();			
  			if(D){
  				out<<static_cast<uint32_t>(len+2);
  				if( out.m_end - out.m_current < static_cast<int32_t>(len+2) ){
  					out.m_good = false;
  					return out;
  				}
  				memcpy(out.m_current,value.c_str(),len);
  				out.m_current += len;
                *(out.m_current) = static_cast<char>(0);
                out.m_current += 1;
                *(out.m_current) = static_cast<char>(0);
                out.m_current += 1;
  			}else{
  				if( out.m_current - out.m_begin < static_cast<int32_t>(len+2) ){
  					out.m_good = false;
  					return out;
  				}
  				out<<static_cast<char>(0)<<static_cast<char>(0);
  				out.m_current -= len;
  				memcpy(out.m_current,value.c_str(),len);				
  				out<<static_cast<uint32_t>(len+2);
  			}
  			if(D){
  				if( out.m_current == out.m_end ) out.m_eof = true;
  			}
  			else{
  				if( out.m_current == out.m_begin ) out.m_eof = true;
  			}
  			return out;
  		}
		
				
  		friend BinOutputPacket& operator<<(BinOutputPacket& out, char* value)
  		{
  			if(!out.m_good || out.m_eof) return out;
  			uint32_t len = strlen(value);
  			if(D){
  				out<<static_cast<uint32_t>(len+2);
  				if( out.m_end - out.m_current < (len+2) ){
  					out.m_good = false;
  					return out;
  				}
  				memcpy(out.m_current,value,len);
  				*(out.m_current+len) = static_cast<char>(0);
  				*(out.m_current+len+1) = static_cast<char>(0);
  				out.m_current += static_cast<uint32_t>(len+2);
  			}else{
  				if( out.m_current - out.m_begin < (len+2) ){
  					out.m_good = false;
  					return out;
  				}
  				out<<static_cast<char>(0)<<static_cast<char>(0);	
  				out.m_current -= len;
  				memcpy(out.m_current,value,len);				
  				out<<static_cast<uint32_t>(len+2);
  			}
  			if(D){
  				if( out.m_current == out.m_end ) out.m_eof = true;
  			}
  			else{
  				if( out.m_current == out.m_begin ) out.m_eof = true;
  			}
  			return out;
  		}

  		friend BinOutputPacket& operator<<(BinOutputPacket& out, PSTR value)
  		{
  			if(!out.m_good || out.m_eof) return out;
  			if(D){
  				out<<static_cast<uint32_t>(value.len+2);
  				if( out.m_end - out.m_current < static_cast<int32_t>(value.len+2) ){
  					out.m_good = false;
  					return out;
  				}
  				memcpy(out.m_current,value.data,value.len);
  				*(out.m_current+value.len) = static_cast<char>(0);
  				*(out.m_current+value.len+1) = static_cast<char>(0);
  				out.m_current += static_cast<uint32_t>(value.len+2);
  			}else{
  				if( out.m_current - out.m_begin < static_cast<int32_t>(value.len+2) ){
  					out.m_good = false;
  					return out;
  				}
  				out<<static_cast<char>(0)<<static_cast<char>(0);	
  				out.m_current -= value.len;
  				memcpy(out.m_current,value.data,value.len);				
  				out<<static_cast<uint32_t>(value.len+2);
  			}
  			if(D){
  				if( out.m_current == out.m_end ) out.m_eof = true;
  			}
  			else{
  				if( out.m_current == out.m_begin ) out.m_eof = true;
  			}
  			return out;
  		}

  		friend BinOutputPacket& operator<<(BinOutputPacket& out, BSTR value)
  		{
            out<<value.len;
            return out.write(value.data,value.len);
  		}

  		friend BinOutputPacket& operator<<(BinOutputPacket& out, BNSTR value)
  		{
            out<<value.len;
            return out.write(value.data,value.len);
  		}

  		friend BinOutputPacket& operator<<(BinOutputPacket& out, NSTR value)
  		{
  			if(!out.m_good || out.m_eof) return out;
  			if(D){
  				out<<static_cast<uint32_t>(value.len+2);
  				if( out.m_end - out.m_current < static_cast<int32_t>(value.len+2) ){
  					out.m_good = false;
  					return out;
  				}
  				memcpy(out.m_current,value.data,value.len);
  				*(out.m_current+value.len) = static_cast<char>(0);
  				*(out.m_current+value.len+1) = static_cast<char>(0);
  				out.m_current += static_cast<uint32_t>(value.len+2);
  			}else{
  				if( out.m_current - out.m_begin < static_cast<int32_t>(value.len+2) ){
  					out.m_good = false;
  					return out;
  				}
  				out<<static_cast<char>(0)<<static_cast<char>(0);	
  				out.m_current -= value.len;
  				memcpy(out.m_current,value.data,value.len);				
  				out<<static_cast<uint32_t>(value.len+2);
  			}
  			if(D){
  				if( out.m_current == out.m_end ) out.m_eof = true;
  			}
  			else{
  				if( out.m_current == out.m_begin ) out.m_eof = true;
  			}
  			return out;
  		}
  };

}
#endif
