#ifndef MODBUS_COMMANDS_HPP
#define MODBUS_COMMANDS_HPP

#include "ModbusCommand.hpp"
#include "ModbusCommandsMap.hpp"


#include "ModbusReadCoilsCommand.hpp"
#include "ModbusReadDiscreteInputs.hpp"
#include "ModbusReadInputRegistersCommand.hpp"
#include "ModbusReadHoldingRegistersCommand.hpp"
#include "ModbusWriteCoilCommand.hpp"
#include "ModbusWriteRegisterCommand.hpp"
#include "ModbusConnectCommand.hpp"
#include "ModbusHelpCommand.hpp"
#include "ModbusExitCommand.hpp"
#include "ModbusFormatCommand.hpp"


class ModbusCommands {
public:
    inline                          ModbusCommands();
    inline void                     exec(ModbusClient& client, const std::string& line);

private:
    inline void                     show_commands_list();
    inline void                     show_command_help(const std::string& cmd);
    inline static void              parse_cmd_line(const std::string& line, std::string& cmd, std::vector<std::string>& args);
    ModbusCommandsMap               m_commands;
};


ModbusCommands::ModbusCommands() :
    m_commands()
{
    m_commands["exit"] = std::make_shared<ModbusExitCommand>();
    m_commands["quit"] = m_commands["exit"];
    m_commands["format"] = std::make_shared<ModbusFormatCommand>();
    m_commands["connect"] = std::make_shared<ModbusConnectCommand>();
    m_commands["readcoils"] = std::make_shared<ReadCoilsCommand>();
    m_commands["readinputs"] = std::make_shared<ReadDiscreteInputs>();
    m_commands["readinputregs"] = std::make_shared<ModbusReadInputRegistersCommand>();
    m_commands["readholdingregs"] = std::make_shared<ModbusReadHoldingRegistersCommand>();
    m_commands["writecoil"] = std::make_shared<ModbusWriteCoilCommand>();
    m_commands["writeregister"] = std::make_shared<ModbusWriteRegisterCommand>();

    auto help_cmd = std::make_shared<ModbusHelpCommand>(m_commands);
    m_commands["help"] = help_cmd;
}


void ModbusCommands::exec(ModbusClient& client, const std::string& line) {
    std::string cmd;
    std::vector<std::string> args;
    parse_cmd_line(line, cmd, args);

    auto cmdobj = m_commands.find(cmd);

    if (cmdobj == m_commands.end()) {
        std::cout << "No such command" << std::endl;
    } else
        cmdobj->second->exec(client, args);
}


void ModbusCommands::parse_cmd_line(const std::string& line, std::string& cmd, std::vector<std::string>& args) {
    namespace po = boost::program_options;

    auto pos = line.find(" ");

    if (pos == std::string::npos) {
        cmd = line;
        args.clear();
    } else {
        cmd = line.substr(0, pos);
        std::string remainder(line.begin()+pos+1, line.end());
        args = po::split_unix(remainder);
    }
}

#endif
