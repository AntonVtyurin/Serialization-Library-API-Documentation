
namespace Serialization
{
    /// Сериализует указанный объект inValue типа Т во входной буфер.
    /// @tparam T            Тип объекта.
    /// @tparam _extent      Extent входного буфера.
    /// @param  buffer       Входной буфер.
    /// @param  inValue      Объект для сериализации.
    /// @param  targetEndian Порядок байтов в результате.
    /// @return              buffer со смещением.
    template <typename T, size_t _extent>
    auto serialize(std::span<std::byte, _extent> buffer, const T &inValue, std::endian targetEndian) noexcept
    {
        // Для каждого более сложного типа объекта следует написать собственные
        // функции сериализации и десериализации, каждая из которых будет
        // выполнять соответствующую операцию над данным сложным типом.
        // Эти функции должны находиться в отдельном заголовочном файле (от заголовочного
        // файла типа) по причине уменьшения времени компиляции и должны подключаться при
        // необходимости использования функций сериализации/десериализации.
        // Следующая проверка предотвращает использование данной функции в
        // случаях, когда заголовочный файл не подключен и/или поиск по ADL не смог найти
        // требуемую функцию для сериализации/десериализации.
        static_assert(std::is_arithmetic_v<T> || std::is_enum_v<T>);
    }

    /// Сериализует указанный объект object типа Т во входной буфер.
    /// @tparam T       Тип объекта.
    /// @tparam _size   Размер входного буфера.
    /// @param  buffer  Входной буфер.
    /// @param  object  Объект для сериализации.
    /// @param  endian  Порядок байтов во входном буфере.
    /// @return         span.
    template <typename T, std::size_t _size>
    constexpr auto serialize(std::array<std::byte, _size> &buffer, const T &object, std::endian endian) noexcept;

    /// Десериализует входной буфер в указанный объект resultValue типа Т
    /// @tparam T             Тип объекта.
    /// @tparam _extent       Extent входного буфера.
    /// @param  buffer        Входной буфер.
    /// @param  resultValue   Десериализованный выходной объект.
    /// @param  sourceEndian  Порядок байтов во входном буфере.
    /// @return               buffer со смещением.
    template <typename T, size_t _extent>
    auto deserialize(std::span<const std::byte, _extent> buffer, T &resultValue, std::endian sourceEndian) noexcept;

    /// Десериализует входной буфер в указанный объект типа Т,
    /// при полном соответствии экстента входного буфера и требуемого экстента буфера
    /// для десериализации типа.
    /// @tparam T        Тип объекта.
    /// @tparam _extent  Extent входного буфера.
    /// @param  buffer   Входной буфер.
    /// @param  endian   Порядок байтов во входном буфере.
    /// @return          Результат десериализации.
    template <typename T, size_t _extent>
    constexpr auto deserialize(std::span<const std::byte, _extent> buffer, std::endian endian) noexcept;

    /// Десериализует входной буфер в указанный объект object типа T
    /// @tparam T       Тип объекта.
    /// @tparam _size   Размер входного буфера.
    /// @param  buffer  Входной буфер.
    /// @param  object  Десериализованный выходной объект.
    /// @param  endian  Порядок байтов во входном буфере.
    /// @return         span.
    template <typename T, std::size_t _size>
    constexpr auto deserialize(const std::array<std::byte, _size> &buffer, T &object, std::endian endian) noexcept;

    /// Десериализует входной буфер в указанный объект типа Т,
    /// при полном соответствии размера входного буфера и требуемого размера буфера
    /// для десериализации типа.
    /// @tparam T       Тип объекта.
    /// @tparam _size   Размер входного буфера.
    /// @param  buffer  Входной буфер.
    /// @param  endian  Порядок байтов во входном буфере.
    /// @return         Результат десериализации.
    template <typename T, std::size_t _size>
    constexpr auto deserialize(const std::array<std::byte, _size> &buffer, std::endian endian) noexcept;

    //*****************************************************************************
    // Сериализация и десериализация групп переменных.
    //*****************************************************************************

    /// Сериализация групп переменных во входной буфер.
    /// @tparam _extent       Extent входного буфера.
    /// @tparam Args          Типы сериализуемых переменных в группе переменных.
    /// @param  buffer        Входной буфер.
    /// @param  targetEndian  Порядок байтов в результате.
    /// @param  args          Сериализуемые переменные.
    /// @return               Неиспользуемая часть входного буфера.
    template <std::size_t _extent, typename... Args>
    constexpr auto serialize(std::span<std::byte, _extent> buffer, std::endian targetEndian, const Args &...args);

    /// Десериализация групп переменных из входного буфера.
    /// @tparam _extent       Extent входного буфера.
    /// @tparam Args          Типы десериализуемых переменных в группе переменных.
    /// @param  buffer        Входной буфер.
    /// @param  sourceEndian  Порядок байт во входном буфере.
    /// @param  args          Десериализуемые переменные.
    /// @return               Неиспользуемая часть входного буфера.
    template <std::size_t _extent, typename... Args>
    constexpr auto deserialize(std::span<const std::byte, _extent> buffer, std::endian sourceEndian, Args &&...args);

}
