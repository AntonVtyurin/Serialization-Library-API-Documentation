
namespace Serialization
{

/// Сериализует inValue в buffer.
/// @tparam T Тип объектов буфера.
/// @tparam _extent Extent входного буфера.
/// @param buffer Входной буфер.
/// @param inValue Объект для сериализации.
/// @param targetEndian Порядок байтов в результате.
/// @return buffer со смещением.
template<typename T, size_t _extent>
auto serialize(std::span<std::byte, _extent> buffer, const T& inValue, std::endian targetEndian) noexcept
{
    // Предполагается, что каждого более сложного типа должна быть написана
    // свои собственные функции сериализации и десериализации, которые будет
    // выполнять соответствующую операцию на данным типом.
    // Эти функции должны находится в отдельном от заголовочного файла типа
    // заголовочном файле по причине уменьшения время компиляции и подключаться
    // при необходимости использования функций сериализации/десериализации.
    // Данная проверка предотвращает использование данной функции в случаях,
    // когда заголовочный файл не подключен и/или поиск по ADL не смог найти
    // требуемую функцию для сериализации/десериализации.
    static_assert(std::is_arithmetic_v<T> || std::is_enum_v<T>);
}

/// Сериализует заданный объект в буфер.
/// @tparam T      Тип объекта.
/// @tparam _size  Размер буфера.
/// @param  buffer Буфер.
/// @param  object Объект для сериализации.
/// @param  endian Порядок байтов.
/// @return span.
template<typename T, std::size_t _size>
constexpr auto serialize(std::array<std::byte, _size>& buffer, const T& object, std::endian endian) noexcept;

/// Десериализует объект типа Т из buffer в resultValue.
/// @tparam T Тип объектов буфера.
/// @tparam _extent Extent входного буфера.
/// @param buffer Входной буфер.
/// @param resultValue Десериализованный выходной объект.
/// @param sourceEndian Порядок байт во входном буфере.
/// @return buffer со смещением.
template<typename T, size_t _extent>
auto deserialize(std::span<const std::byte, _extent> buffer, T& resultValue, std::endian sourceEndian) noexcept;

/// Десериализует буфер в указанный объект,
/// при полном соответствии размера входного буфера и требуемый размера буфера для десериализации типа.
/// @tparam T       Тип объекта.
/// @tparam _extent Extent буфера.
/// @param  buffer  Буфер.
/// @param  endian  Порядок байт во входном буфере.
/// @return Результат десериализации.
template<typename T, size_t _extent>
constexpr auto deserialize(std::span<const std::byte, _extent> buffer, std::endian endian) noexcept;

/// Десериализует буфер в указанный объект,
/// при полном соответствии размера входного буфера и требуемый размера буфера для десериализации типа.
/// @tparam T      Тип объекта.
/// @tparam _size  Размер буфера.
/// @param  buffer Буфер.
/// @param  object Объект для десериализации.
/// @param  endian Порядок байт.
/// @return span.
template<typename T, std::size_t _size>
constexpr auto deserialize(const std::array<std::byte, _size>& buffer, T& object, std::endian endian) noexcept;

/// Десериализует буфер в указанный объект.
/// @tparam T      Тип объекта.
/// @tparam _size  Размер буфера.
/// @param  buffer Буфер.
/// @param  endian Порядок байт во входном буфере.
/// @return Результат десериализации.
template<typename T, std::size_t _size>
constexpr auto deserialize(const std::array<std::byte, _size>& buffer, std::endian endian) noexcept;

//*****************************************************************************
// Сериализация и десериализация групп переменнных.
//*****************************************************************************

/// Сериализация групп переменных в входной буфер байт.
/// @tparam _extent Extent входного буфера байт.
/// @tparam Args Типы сериализуемых переменных в группе переменных.
/// @param buffer Входной буфер байт.
/// @param targetEndian Порядок байтов в результате.
/// @param args Сериализуемые переменные.
/// @return Неиспользуемая часть входного буфера.
template<std::size_t _extent, typename... Args>
constexpr auto serialize(std::span<std::byte, _extent> buffer, std::endian targetEndian, const Args&... args);

/// Десериализация групп переменных из входного буфера байт.
/// @tparam _extent Extent входного буфера байт.
/// @tparam Args Типы десериализуемых переменных в группе переменных.
/// @param buffer Входной буфер байт.
/// @param sourceEndian Порядок байт во входном буфере.
/// @param args Десериализуемые переменные.
/// @return Неиспользуемая часть входного буфера.
template<std::size_t _extent, typename... Args>
constexpr auto deserialize(std::span<const std::byte, _extent> buffer, std::endian sourceEndian, Args&&... args);

}
