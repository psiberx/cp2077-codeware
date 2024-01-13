#include "SpdlogProvider.hpp"
#include "Core/Facades/Runtime.hpp"
#include "Core/Stl.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

void Support::SpdlogProvider::OnInitialize()
{
    if (m_logPath.empty())
    {
        m_logPath = Core::Runtime::GetModulePath().replace_extension(L".log");
    }

    if (m_appendTimestamp)
    {
        // Append timestamp to filename
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm = *std::localtime(&now_c);

        const auto timestamp =
            fmt::format("-{:04d}-{:02d}-{:02d}-{:02d}-{:02d}-{:02d}", now_tm.tm_year + 1900, now_tm.tm_mon + 1,
                        now_tm.tm_mday, now_tm.tm_hour, now_tm.tm_min, now_tm.tm_sec);

        const auto extension = m_logPath.extension().string();
        m_logPath = m_logPath.replace_extension();

        m_logPath += timestamp;
        m_logPath.replace_extension(extension);
    }

    auto sink = Core::MakeShared<spdlog::sinks::basic_file_sink_mt>(m_logPath.string(), true);
    auto logger = Core::MakeShared<spdlog::logger>("", spdlog::sinks_init_list{sink});
    logger->flush_on(spdlog::level::trace);

    spdlog::set_default_logger(logger);
    spdlog::set_level(spdlog::level::trace);

    SetDefault(*this);
}

void Support::SpdlogProvider::LogInfo(const std::string_view& aMessage)
{
    spdlog::default_logger_raw()->info(aMessage);
}

void Support::SpdlogProvider::LogWarning(const std::string_view& aMessage)
{
    spdlog::default_logger_raw()->warn(aMessage);
}

void Support::SpdlogProvider::LogError(const std::string_view& aMessage)
{
    spdlog::default_logger_raw()->error(aMessage);
}

void Support::SpdlogProvider::LogDebug(const std::string_view& aMessage)
{
    spdlog::default_logger_raw()->debug(aMessage);
}

void Support::SpdlogProvider::LogFlush()
{
    spdlog::default_logger_raw()->flush();
}
