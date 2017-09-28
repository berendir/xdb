#include "db3_table.h"
#include "errors.h"
#include "utils.h"

using namespace xdb;
using namespace std;


db3_table::db3_table(const std::string &file_name) :
    table_base(file_name)
{
    m_stm.open(m_file_name);

    if (!m_stm.is_open())
        XDB_IO_ERROR("XDBXXXX", "Impossible to open file");

    m_stm.read((char*) &m_header, sizeof(m_header));

    if (m_header.version != DB3_TYPE_MEMO && m_header.version != DB3_TYPE_NO_MEMO)
        XDB_THROW_EXCEPTION("XDBXXXX", "Unsupported file type");

    m_stm.close();
}

void db3_table::open()
{
    m_stm.open(m_file_name);

    if (!m_stm.is_open())
        XDB_IO_ERROR("XDBXXXX", "Impossible to open file");

    const int HEADER_SIZE = sizeof(db3_header);
    const int FIELD_DESCRIPTOR_SIZE = sizeof(db3_field_descriptor);

    int64_t calculated_file_size = m_header.header_size;
    calculated_file_size += m_header.record_size * m_header.record_count;
    calculated_file_size += 1;

    if (file_size(m_file_name) != calculated_file_size)
        XDB_VALIDATION_ERROR("XDBXXXX", "File size verification failed");

    int field_count = (m_header.header_size - HEADER_SIZE) / FIELD_DESCRIPTOR_SIZE;

    m_field_descriptors.resize(field_count);

    m_stm.read((char*) m_field_descriptors.data(), FIELD_DESCRIPTOR_SIZE * field_count);

    if (m_stm.get() != 0x0D)
        XDB_VALIDATION_ERROR("XDBXXXX", "Field descriptors delimiter not found");
}

void db3_table::close()
{
    m_stm.close();
}

int db3_table::size() const
{
    return m_stm.is_open() ? m_header.record_count : -1;
}
