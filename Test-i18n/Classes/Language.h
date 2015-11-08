//
//  Language.h
//  Test_i18n
//
//  Created by Konvie Shaw on 15/10/29.
//
//

#ifndef Language_h
#define Language_h

#include "cocos2d.h"
USING_NS_CC;

#define LocalizedCStringByKey(key) Language::getStringByKey(key)
#define LocalizedFontTypeNormal Language::getFontTypeNormal()

class  Language{
    
public:
    
    static const char* getStringByKey(const char * key)
    {
        
        // 获取当前系统环境语言类型
        LanguageType languageType = Application::getInstance()->getCurrentLanguage();
        
        // 字典
        __Dictionary *pDic;
        
        if(LanguageType::CHINESE == languageType)
            //根据语言选择不同的属性表
            pDic = __Dictionary::createWithContentsOfFile("zh.plist");
        else
            pDic = __Dictionary::createWithContentsOfFile("en.plist");
        
        std::string keyStr = key;
        
        //返回key对应的value
        return (pDic -> valueForKey(keyStr))->getCString();
    }
    
    
    static const char* getFontTypeNormal()
    {
        const char* csRet;
        
        LanguageType languageType = Application::getInstance()->getCurrentLanguage();

        if(LanguageType::CHINESE == languageType)
            //根据语言选择不同的属性表
            csRet = "STHeitiSC-Light";
        else
            csRet = "AmericanTypewriter-Bold";
        
        return csRet;
    }
    
};

#endif /* Language_h */
