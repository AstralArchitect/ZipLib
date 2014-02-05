#pragma once
#include <iostream>

struct compression_properties_interface
{
  virtual void normalize() = 0;
};

struct compression_encoder_properties_interface
  : compression_properties_interface
{

};

struct compression_decoder_properties_interface
  : compression_properties_interface
{

};

template <typename ELEM_TYPE, typename TRAITS_TYPE>
class compression_interface_basic
{
  public:
    typedef std::basic_istream<ELEM_TYPE, TRAITS_TYPE> istream_t;
    typedef std::basic_ostream<ELEM_TYPE, TRAITS_TYPE> ostream_t;

    virtual ~compression_interface_basic() { }

    virtual bool is_init() const = 0;

    virtual size_t get_bytes_read() const = 0;
    virtual size_t get_bytes_written() const = 0;

    virtual ELEM_TYPE* get_buffer_begin() = 0;
    virtual ELEM_TYPE* get_buffer_end() = 0;
};

template <typename ELEM_TYPE, typename TRAITS_TYPE>
class compression_encoder_interface_basic
  : public compression_interface_basic<ELEM_TYPE, TRAITS_TYPE>
{
  public:
    typedef typename compression_interface_basic<ELEM_TYPE, TRAITS_TYPE>::istream_t istream_t;
    typedef typename compression_interface_basic<ELEM_TYPE, TRAITS_TYPE>::ostream_t ostream_t;

    virtual void init(ostream_t& stream) = 0;
    virtual void init(ostream_t& stream, compression_encoder_properties_interface& props) = 0;
    virtual void encode_next(size_t length) = 0;
    virtual void sync() = 0;
};

template <typename ELEM_TYPE, typename TRAITS_TYPE>
class compression_decoder_interface_basic
  : public compression_interface_basic<ELEM_TYPE, TRAITS_TYPE>
{
  public:
    typedef typename compression_interface_basic<ELEM_TYPE, TRAITS_TYPE>::istream_t istream_t;
    typedef typename compression_interface_basic<ELEM_TYPE, TRAITS_TYPE>::ostream_t ostream_t;

    virtual void init(istream_t& stream) = 0;
    virtual void init(istream_t& stream, compression_decoder_properties_interface& props) = 0;
    virtual size_t decode_next() = 0;
};

typedef compression_interface_basic<uint8_t, std::char_traits<uint8_t>>           byte_compression_interface;
typedef compression_interface_basic<char, std::char_traits<char>>                 compression_interface;
typedef compression_interface_basic<wchar_t, std::char_traits<wchar_t>>           wcompression_interface;

typedef compression_encoder_interface_basic<uint8_t, std::char_traits<uint8_t>>   byte_compression_encoder_interface;
typedef compression_encoder_interface_basic<char, std::char_traits<char>>         compression_encoder_interface;
typedef compression_encoder_interface_basic<wchar_t, std::char_traits<wchar_t>>   wcompression_encoder_interface;

typedef compression_decoder_interface_basic<uint8_t, std::char_traits<uint8_t>>   byte_compression_decoder_interface;
typedef compression_decoder_interface_basic<char, std::char_traits<char>>         compression_decoder_interface;
typedef compression_decoder_interface_basic<wchar_t, std::char_traits<wchar_t>>   wcompression_decoder_interface;