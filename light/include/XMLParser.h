#pragma once

#include <map>
#include <vector>

#include "Markup.h"
#include "XMLConverter.h"

namespace light
{

class XMLParser
{
private:
    typedef unsigned short DEPTH;

    typedef std::map<std::wstring, XML_CONVETER::CONVERT_INFO> MAP_BIND;

public:
    XMLParser();

    ~XMLParser();

    bool read_doc(const std::wstring& strXML);

    bool read_file(const std::wstring& strFile);

    bool execute(const std::wstring& Elem);

    /// XML ���ڿ� �о��
    std::wstring read_doc()
    {
        return m_markup.GetDoc();
    }

    bool next();

public:  // get_elem ���� �޼ҵ�
    template <typename T>
    bool get_elem(const std::wstring& Elem, T& t)
    {
        XML_CONVETER::TYPE type = XML_CONVETER::convert_type(t);
        if (type == XML_CONVETER::DENIED)
            return false;

        return bind_get_elem(type, Elem, &t, sizeof(t));
    }

    /// Ư�� ������Ʈ �ȿ� ���Ե� Attrib�� ���ڿ� ��ü�� ���ε� �����ִ� �޼ҵ�
    bool get_elem(const std::wstring& Elem, WCHAR* str, size_t get_length)
    {
        XML_CONVETER::TYPE type = XML_CONVETER::convert_type(str);
        if (type == XML_CONVETER::DENIED)
            return false;

        return bind_get_elem(type, Elem, str, get_length);
    }

    /// ���� Elem�� �� ������ �޼ҵ�
    const std::wstring get_elem();

    /// ���� Elem�� �� ������ �޼ҵ�
    const int get_elem_to_integer()
    {
        return _ttoi(get_elem().c_str());
    }

    /// ���� Elem�� �� ������ �޼ҵ�
    const double get_elem_to_double()
    {
        return _tstof(get_elem().c_str());
    }

    /// Depth�� ���ߴ� �޼ҵ�
    bool out();

private:
    /// Ư�� ������Ʈ �ȿ� ���Ե� Attrib�� ���ۿ� ���ε� �����ִ� �޼ҵ�
    bool bind_get_elem(const XML_CONVETER::TYPE type, const std::wstring& Elem, void* ptr, size_t get_length)
    {
        if (false == bind_elem(Elem))
            return false;

        if (false == next())
            return false;

        XML_CONVETER::CONVERT_INFO ConvertInfo(type, get_length, ptr);
        if (false == XML_CONVETER::convert(get_elem(), ConvertInfo))
            return false;

        next();
        return true;
    }

    /// �ش� Ÿ���� �Ѿ���� ������ �ȵǰ� �ϱ� ���� �����
    bool get_elem(const std::wstring& Elem, const WCHAR* str);

    /// �ش� Ÿ���� �Ѿ���� ������ �ȵǰ� �ϱ� ���� �����
    bool get_elem(const std::wstring& Elem, WCHAR* str);

public: // bind �迭 �޼ҵ�

        /// ���� ����
    bool bind_elem(const std::wstring& strElem);

    /// Ư�� ������Ʈ �ȿ� ���Ե� Attrib�� ���ڿ� ��ü�� ���ε� �����ִ� �޼ҵ�
    template <typename T>
    bool bind_attrib(const std::wstring& Attrib, T& Data)
    {
        const XML_CONVETER::TYPE type = XML_CONVETER::convert_type(Data);
        if (type == XML_CONVETER::DENIED)
            return false;

        return bind_attrib(type, Attrib, &Data, sizeof(Data));
    }

    /// Ư�� ������Ʈ �ȿ� ���Ե� Attrib�� ���ڿ� ��ü�� ���ε� �����ִ� �޼ҵ�
    bool bind_attrib(const std::wstring& Attrib, WCHAR* Str, size_t get_length)
    {
        const XML_CONVETER::TYPE type = XML_CONVETER::convert_type(Str);
        if (type == XML_CONVETER::DENIED)
            return false;

        return bind_attrib(type, Attrib, Str, get_length);
    }

private: /// �ش� Ÿ���� �Ѿ���� ������ �ȵǰ� �ϱ� ���� �����
    bool bind_attrib(const std::wstring& Attrib, const WCHAR* Str);

    bool bind_attrib(const std::wstring& Attrib, WCHAR* Str);

private:
    /// Ư�� ������Ʈ �ȿ� ���Ե� Attrib�� ���ۿ� ���ε� �����ִ� �޼ҵ�
    bool bind_attrib(const XML_CONVETER::TYPE Type, const std::wstring& Attrib, void* ptr, size_t get_length)
    {
        auto& binds = map();
        auto Ret = binds.insert((MAP_BIND::value_type(elem_wstring() + L"_" + Attrib, XML_CONVETER::CONVERT_INFO(Type, get_length, ptr))));
        return Ret.second;
    }

private:
    /// �����̳� ũ�� ������ �޼ҵ�
    void resize();

    /// Depth�� ���̴� �޼ҵ�
    bool into();

    /// ���� ������Ʈ�� �о� ���ε�� ���ڿ��� ��� �޼ҵ�
    bool read_elem();

    /// ��ġ ���� ���
    void reset_pos()
    {
        m_markup.ResetMainPos();
    }

private: // �ܼ� ����. � �޼ҵ带 ����ϴ� ���� �����ϱ� ����.

            /// Elem ������ ã�� �޼ҵ�
    bool find_elem(const std::wstring& Elem);

    /// ChildElem ������ ã�� �޼ҵ�
    bool find_child_elem(const std::wstring& Elem);

    /// Attrib�� ���� ���� �޼ҵ�
    const std::wstring get_attrib(const std::wstring& Attrib);

    /// ChildAttrib�� ���� ���� �޼ҵ�
    const std::wstring get_child_attrib(const std::wstring& Attrib);

private: // ���� Depth�� �ش��ϴ� �ڷᱸ���� ������ �޼ҵ�

            /// ���� Depth�� �ش�Ǵ� Elem�� ������ �޼ҵ�
    const std::wstring& elem_wstring();

    /// Element ���ڿ� ����
    void elem_wstring(const std::wstring& str);

    /// ���� Depth�� �ش�Ǵ� Attrib map�� ������ �޼ҵ�
    MAP_BIND& map();

    /// into �÷��� ���� �޼ҵ�
    void into_flag(bool bFlag);

    /// into �÷��� ��ȯ �޼ҵ�
    bool into_flag();

private:
    std::vector<std::wstring> m_elems;

    std::vector<MAP_BIND> m_bind_attribs;

    std::vector<bool> m_into_flag;

    DEPTH m_depth;

    CMarkup m_markup;
};

} //namespace light