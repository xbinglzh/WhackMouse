//
//  GameUtils.cpp
//  MetalWar
//
//  Created by xUanBing on 12-7-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "GameUtils.h"

#include <math.h>
#include "HMD5.h"

using namespace cocos2d;

#ifndef SWAP_VALUE
    #define SWAP_VALUE(x,y) {t = *x;*x = *y;*y = t;}
#endif


static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static inline bool is_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

const char* get0CharString(const int32_t number)
{
    return CCString::createWithFormat("%02d", number)->getCString();
}

std::wstring GameUtils::UTF2Uni(const char* src, std::wstring &t)
{
    if (src == NULL) 
    {
        return L"";
    }
	
    int size_s = strlen(src);
    int size_d = size_s + 10;          //?
	
    wchar_t *des = new wchar_t[size_d];
    memset(des, 0, size_d * sizeof(wchar_t));
	
    int s = 0, d = 0;
//    bool toomuchbyte = true; //set true to skip error prefix.
	
    while (s < size_s && d < size_d)
    {
        unsigned char c = src[s];
        if ((c & 0x80) == 0) 
        {
            des[d++] += src[s++];
        } 
        else if((c & 0xE0) == 0xC0)  ///< 110x-xxxx 10xx-xxxx
        {
            wchar_t &wideChar = des[d++];
            wideChar  = (src[s + 0] & 0x3F) << 6;
            wideChar |= (src[s + 1] & 0x3F);
			
            s += 2;
        }
        else if((c & 0xF0) == 0xE0)  ///< 1110-xxxx 10xx-xxxx 10xx-xxxx
        {
            wchar_t &wideChar = des[d++];
			
            wideChar  = (src[s + 0] & 0x1F) << 12;
            wideChar |= (src[s + 1] & 0x3F) << 6;
            wideChar |= (src[s + 2] & 0x3F);
			
            s += 3;
        } 
        else if((c & 0xF8) == 0xF0)  ///< 1111-0xxx 10xx-xxxx 10xx-xxxx 10xx-xxxx 
        {
            wchar_t &wideChar = des[d++];
			
            wideChar  = (src[s + 0] & 0x0F) << 18;
            wideChar  = (src[s + 1] & 0x3F) << 12;
            wideChar |= (src[s + 2] & 0x3F) << 6;
            wideChar |= (src[s + 3] & 0x3F);
			
            s += 4;
        } 
        else 
        {
            wchar_t &wideChar = des[d++]; ///< 1111-10xx 10xx-xxxx 10xx-xxxx 10xx-xxxx 10xx-xxxx 
			
            wideChar  = (src[s + 0] & 0x07) << 24;
            wideChar  = (src[s + 1] & 0x3F) << 18;
            wideChar  = (src[s + 2] & 0x3F) << 12;
            wideChar |= (src[s + 3] & 0x3F) << 6;
            wideChar |= (src[s + 4] & 0x3F);
			
            s += 5;
        }
    }
	
    t = des;
    delete[] des;
    des = NULL;
	
    return t;
}

std::string GameUtils::Char2Hex(char a)
{
    std::string str = "";
    int n = a;
    for (int i = 2*sizeof(char) - 1; i >= 0; i--)
    {
        str += "0123456789ABCDEF"[((n >> i*4) & 0xF)];
    }
    return str;
}

unsigned int GameUtils::Hex2Int(const char* str, int len)
{
	int i;
	unsigned int s=0;
	for(i=0;i<len;i++)
	{
		if(str[i]=='\0')
			return s;
		if(str[i]>='0'&&str[i]<='9')
		{
			s<<=4;
			s|=(str[i]-'0');
		}
		else
		{
			switch(str[i])
			{
				case 'a':
				case 'A':s<<=4;s|=0x0A;break;
				case 'b':
				case 'B':s<<=4;s|=0x0B;break;
				case 'c':
				case 'C':s<<=4;s|=0x0C;break;
				case 'd':
				case 'D':s<<=4;s|=0x0D;break;
				case 'e':
				case 'E':s<<=4;s|=0x0E;break;
				case 'f':
				case 'F':s<<=4;s|=0x0F;break;
				default:return 0;
			}
		}
	}
	return s;
}


char * GameUtils::ByteToHex(const unsigned char* vByte, const int vLen)
{
	if(!vByte) 
		return NULL;
	
	char* tmp = new char[vLen * 2 + 1]; // 一个字节两个十六进制码，最后要多一个'\0'
	
	int tmp2;
	for (int i=0;i<vLen;i++)
	{
		tmp2 = (int)(vByte[i])/16;
		tmp[i*2] = (char)(tmp2+((tmp2>9)?'A'-10:'0'));
		tmp2 = (int)(vByte[i])%16;
		tmp[i*2+1] = (char)(tmp2+((tmp2>9)?'A'-10:'0'));
	}
	
	tmp[vLen * 2] = '\0';
	return tmp;
}


unsigned char* GameUtils::HexToByte(const char* szHex,const int iLen)
{
	if(!szHex) 
		return NULL;
	
	//int iLen = strlen(szHex);
	
	if (iLen<=0 || 0 != iLen%2) 
		return NULL;
	
	unsigned char* pbBuf = new unsigned char[iLen/2];  // 数据缓冲区
	
	int tmp1, tmp2;
	for (int i=0;i<iLen/2;i++)
	{
		tmp1 = (int)szHex[i*2] - (((int)szHex[i*2]>='A')?'A'-10:'0');
		
		if(tmp1>=16) 
			return NULL;
		
		tmp2 = (int)szHex[i*2+1] - (((int)szHex[i*2+1]>='A')?'A'-10:'0');
		
		if(tmp2>=16)
			return NULL;
		
		pbBuf[i] = (tmp1*16+tmp2);
	}
	
	return pbBuf;
}

std::string GameUtils::stringReplace(const std::string &strbig, const std::string &str, const std::string &strdst) {
    std::string::size_type pos = 0;
    std::string::size_type strlen = str.size();
    std::string::size_type dstlen = strdst.size();
    std::string replace = strbig;
    
    while ((pos = replace.find(str, pos)) != std::string::npos) {
        replace.replace(pos, strlen, strdst);
        pos += dstlen;
    }
    return replace;
}


std::string GameUtils::utf82ucs2(const char * aBufUTF8)
{
	std::wstring t;
	UTF2Uni(aBufUTF8,t);
	std::string sb;
	int i,j;
	for (i = 0; i < t.length(); i++)
	{
		const wchar_t & c = t[i];
		sb.append("\\u");
		j = (c >>8); //取出高8位
        std::string tmp = Char2Hex(j);
		if (tmp.length() == 1)
			sb.append("0");
		
		sb.append(tmp);
		
		j = (c & 0xFF); //取出低8位
		tmp = Char2Hex(j);
		if (tmp.length() == 1)
			sb.append("0");
		sb.append(tmp);
	} 
	
	return sb;
}

void GameUtils::encryptRC4(char * aBuffer,int aBufferLength, const char *aToken,int aTokenLength)
{
	int index;
	char t;
	unsigned char m_box[256];
	
	//生成对应的Key
	int seed_len = aTokenLength;
	unsigned char * seed = (unsigned char *)aToken;
	
	int src_len=aBufferLength;
	unsigned char  * src = (unsigned char *)aBuffer;
	
	int i;
	for( i = 0 ; i < 256 ; i++ )
	{
		m_box[i] = i;//s-box
	}
	
	int j = 0;
	for( i = 0 ; i < 256 ; i++ )
	{
		j = (j + seed[i%seed_len] + m_box[i])%256;//搅乱s-box
		SWAP_VALUE(&m_box[i],&m_box[j]);
	}
	
	int x = 0;
	int y = 0;
	for( i = 0 ; i < src_len ; i++)
	{
		x = (x + 1) % 256;
		y = (m_box[x] + y) % 256;
		SWAP_VALUE(&m_box[x],&m_box[y]);
		index = (m_box[x] + m_box[y]) % 256;
		t = *(src+i);
		t ^= m_box[index];//m_box[index]变成sub-key
		*(src+i) = t;
	}
}

const std::string GameUtils::makeStringMd5(const char * text){
    std::string md5String = "";
    if (text) {
        HMD5 file_name = HMD5(text);
        md5String = file_name.hexdigest();
    }
    return md5String;
}


std::string GameUtils::base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
	
    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
			
            for(i = 0; (i <4) ; i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }
	
    if (i)
    {
        for(j = i; j < 3; j++)
            char_array_3[j] = '\0';
		
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;
		
        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];
		
        while((i++ < 3))
            ret += '=';
		
    }
	
    return ret;
	
}

std::string GameUtils::base64_decode(std::string const& encoded_string) {
    int in_len = encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;
	
    while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i ==4) {
            for (i = 0; i <4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);
			
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
			
            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }
	
    if (i) {
        for (j = i; j <4; j++)
            char_array_4[j] = 0;
		
        for (j = 0; j <4; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);
		
        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
		
        for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
    }
	
    return ret;
}

std::string GameUtils::timeToString(const float secondsElapsed){
	std::string str="";
    
	int mm = ((int)secondsElapsed) / 60;
	int ss = ((int)secondsElapsed) % 60;
	int hh = mm / 60;
	mm = mm % 60;
	
    if(hh != 0) {
        std::stringstream h_num;
        h_num << hh;
        if (hh < 10) {
            str.append("0");
        }
        str.append(h_num.str());
        str.append(":");
    }
	
	std::stringstream m_num;
	m_num << mm;
	if (mm < 10) {
		str.append("0");
	}
	str.append(m_num.str());
	str.append(":");
	
	
	std::stringstream s_num;
	s_num << ss;
	if (ss < 10) {
		str.append("0");
	}
	str.append(s_num.str());
	
	return str;
}

std::string GameUtils::timeToStringFormat(const float secondsElapsed) {
    std::string str="";
    
	int mm = ((int)secondsElapsed) / 60;
	int ss = ((int)secondsElapsed) % 60;
	int hh = mm / 60;
	mm = mm % 60;
	
    std::stringstream h_num;
    h_num << hh;
    if (hh < 10) {
        str.append("0");
    }
    str.append(h_num.str());
    str.append(":");
	
	std::stringstream m_num;
	m_num << mm;
	if (mm < 10) {
		str.append("0");
	}
	str.append(m_num.str());
	str.append(":");
	
	
	std::stringstream s_num;
	s_num << ss;
	if (ss < 10) {
		str.append("0");
	}
	str.append(s_num.str());
	
	return str;

}

std::string GameUtils::RC4WithToken(const std::string & text,const std::string & token)
{
	std::string  encryptStr;
	auto len = (text.length() / 2);
	char* hexString=(char *)HexToByte(text.c_str(),text.length());
	encryptRC4(hexString,len, (char *)token.c_str(), token.length());
	char* hex_str = ByteToHex((unsigned char*)hexString, len);
	delete []hexString;
	hexString = NULL;
	encryptStr = hex_str;
	delete []hex_str;
	hex_str = NULL;
	return encryptStr;
}

/*
 对一个字符串转化为Array
 */
const std::vector<std::string>  GameUtils::string2Array(const std::string & text,
                                                        const std::string & tag){
	std::vector<std::string> vals;
	std::string srcString = text;
    size_t startPos = srcString.find_first_of(tag);
    if (startPos != std::string::npos) {
        do {
            std::string tmp = srcString.substr(0,startPos);
            vals.push_back(tmp);
            srcString = srcString.substr(startPos + tag.length());
            startPos = srcString.find_first_of(tag);
        } while (startPos != std::string::npos);
        vals.push_back(srcString);
    }else{
        vals.push_back(text);
    }
    return vals;
}

const std::vector<int32_t>  GameUtils::string2IntArray(const std::string & text,
                                                       const std::string & tag){
    std::vector<int32_t> vals;
	std::string srcString = text;
    size_t startPos = srcString.find_first_of(tag);
    if (startPos != std::string::npos) {
        do {
            std::string tmp = srcString.substr(0,startPos);
            vals.push_back(atoi(tmp.c_str()));
            srcString = srcString.substr(startPos + tag.length());
            startPos = srcString.find_first_of(tag);
        } while (startPos != std::string::npos);
        vals.push_back(atoi(srcString.c_str()));
    }else{
        vals.push_back(atoi(text.c_str()));
    }
    return vals;
}

const cocos2d::Point GameUtils::string2Point(const std::string & text,const std::string & tag){
    cocos2d::Point p;
    const std::vector<std::string> arr = GameUtils::string2Array(text,tag);
    p.x = atof(arr[0].c_str());
    p.y = atof(arr[1].c_str());
    return p;
}

const cocos2d::Size  GameUtils::string2Size(const std::string & text,const std::string & tag){
    cocos2d::Size s;
    const std::vector<std::string> arr = GameUtils::string2Array(text,tag);
    s.width  = atof(arr[0].c_str());
    s.height = atof(arr[1].c_str());
    return s;
}

cocos2d::Rect GameUtils::string2Rect(const std::string & text,const std::string & tag){
    cocos2d::Rect s;
    const std::vector<std::string> arr = GameUtils::string2Array(text,tag);
    s.origin.x = atof(arr[0].c_str());
    s.origin.y = atof(arr[1].c_str());
    s.size.width = atof(arr[2].c_str());
    s.size.height = atof(arr[3].c_str());
    return s;
}

const cocos2d::Point GameUtils::uintVector(const cocos2d::Point & start,
                                       const cocos2d::Point & end){
    cocos2d::Point p = end - start;
    float len = p.getLength();
    p = Vec2(p.x / len, p.y / len);
    return p;
}

const float GameUtils::vector2AngleDegress(const cocos2d::Point & vector){
    return CC_RADIANS_TO_DEGREES(vector.getAngle());
}

const cocos2d::Point GameUtils::angleDegress2uintVector(const float angleDegress){
    float angle_r = CC_DEGREES_TO_RADIANS(angleDegress);
    return cocos2d::Point(cosf(angle_r),sinf(angle_r));
}

const std::string GameUtils::createDefaultRC4Key(const std::string& scretKey) {
    time_t current = time(0);
	std::stringstream timeStr;
	timeStr << current;
    const std::string & time_val  = timeStr.str();
    
    std::stringstream infoKeyStr;
    infoKeyStr << scretKey;
	infoKeyStr << time_val;
    HMD5 infoKeyMd5 = HMD5(infoKeyStr.str());
    const std::string rc4_token = infoKeyMd5.hexdigest();
    return rc4_token;
}

const std::string GameUtils::string_rc4(const std::string &text, const std::string &rc4_token){
    if (text.length() > 0) {
        char * buffer = GameUtils::ByteToHex((const unsigned char* )text.c_str(), text.length());
        const std::string info_val = buffer;
        delete []buffer;
        buffer = NULL;
        return GameUtils::RC4WithToken(info_val, rc4_token);
    }
    return text;
}

void GameUtils::changeOpacity(Node* node,GLubyte opacity){
    
    __RGBAProtocol *pRGBAProtocol = dynamic_cast<__RGBAProtocol*>(node);
    
    if (pRGBAProtocol)
    {
        pRGBAProtocol->setOpacity(opacity);
    }
    
    Vector<Node*> &children = node->getChildren();
    Ref* child = NULL;

    for (int i = 0; i< children.size(); i++) {
        child = children.at(i);
        changeOpacity((Node*)child, opacity);
    }

}

float GameUtils::UiInterfaceScale() {
    float scale = 1.0f;

    return scale;
}
