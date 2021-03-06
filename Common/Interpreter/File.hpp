#ifndef _FILE_HPP_
#define _FILE_HPP_

#include "config.hpp"
#include "Macros.hpp"
#include "Base.hpp"
#include <boost/shared_ptr.hpp>
#include <fstream>

using namespace boost;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    class File
    : public Base<EncodingT>
    {
    private:
         class BaseStream
         {
         public:
             virtual ~BaseStream() = default;
             virtual void open(const typename EncodingT::string_t& name, std::ios_base::openmode mode) = 0;
             virtual void imbue(const std::locale& locale) = 0;
             virtual bool is_open() const = 0;
             virtual void close() = 0;
             virtual int tellg() = 0;
             virtual void seekg(int off, std::ios_base::seekdir dir) = 0;
             virtual void clear() = 0;
             virtual size_t size_of_char() = 0;
             virtual void read(std::vector<uint8_t>& b) = 0;
             virtual void write(const std::vector<uint8_t>& b) = 0;
         };

        template <class CharT>
        class FileStream : public BaseStream
        {
        private:
            std::basic_fstream<CharT> m_fstream;

        public:
            FileStream();
            ~FileStream();
            void open(const typename EncodingT::string_t& name, std::ios_base::openmode mode) override;
            void imbue(const std::locale& locale) override;
            bool is_open() const override;
            void close() override;
            int tellg() override;
            void seekg(int off, std::ios_base::seekdir dir) override;
            void clear() override;
            size_t size_of_char() override;
            void read(std::vector<uint8_t>& b) override;
            void write(const std::vector<uint8_t>& b) override;
        };

        typename EncodingT::string_t  m_name;
        typename EncodingT::string_t  m_mode;
        typename EncodingT::string_t  m_format;
        boost::scoped_ptr<BaseStream> m_stream;

        void construct(const typename EncodingT::string_t& name, const typename EncodingT::string_t& mode, const typename EncodingT::string_t& format);

    public:
        // Constructor
        File();

        File(const typename EncodingT::string_t& name, const typename EncodingT::string_t& mode, const typename EncodingT::string_t& format);

        FACTORY_PROTOTYPE3(File, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        File(boost::shared_ptr< Base<EncodingT> > const& name, boost::shared_ptr< Base<EncodingT> > const& mode, boost::shared_ptr< Base<EncodingT> > const& format);

        // Destructor
        ~File();

        // Virtual methods
        virtual typename EncodingT::string_t toString() const;
        virtual boost::shared_ptr< Base<EncodingT> > clone() const;
        virtual typename EncodingT::string_t getClassName() const;
        virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

        // Dynamic methods
        boost::shared_ptr< Base<EncodingT> > isOpen() const;

        FACTORY_PROTOTYPE1(load, InOut< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > load(boost::shared_ptr< Base<EncodingT> >& val);

        FACTORY_PROTOTYPE1(save, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > save(boost::shared_ptr< Base<EncodingT> > const& val);

        boost::shared_ptr< Base<EncodingT> > size();

        // Methods registration
        FACTORY_BEGIN_REGISTER
            CLASS_REGISTER      (File)
            CLASS_REGISTER3     (File)
            METHOD_KEY_REGISTER (File, boost::shared_ptr< Base<EncodingT> >, isOpen, const_t, UCS("File::Open") )
            METHOD_REGISTER1    (File, boost::shared_ptr< Base<EncodingT> >, load, no_const_t)
            METHOD_REGISTER1    (File, boost::shared_ptr< Base<EncodingT> >, save, no_const_t)
            METHOD_REGISTER     (File, boost::shared_ptr< Base<EncodingT> >, size, no_const_t)
        FACTORY_END_REGISTER

        // Methods unregistration
        FACTORY_BEGIN_UNREGISTER
            CLASS_UNREGISTER      (File)
            CLASS_UNREGISTER3     (File)
            METHOD_KEY_UNREGISTER (UCS("File::Open"))
            METHOD_UNREGISTER1    (File, load)
            METHOD_UNREGISTER1    (File, save)
            METHOD_UNREGISTER     (File, size)
        FACTORY_END_UNREGISTER
    };

NAMESPACE_END

#include "File_impl.hpp"

#endif
