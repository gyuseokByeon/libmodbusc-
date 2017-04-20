#ifndef GENERIC_BACKEND_HPP
#define GENERIC_BACKEND_HPP

class ModbusGenericBackend {
public:
    inline ModbusGenericBackend();

    template <typename Callback>
    void  getCoils(uint16_t startAddr, uint16_t numCoils, Callback cb) {
        for (std::size_t i = startAddr; i < startAddr + numCoils; ++i)
            cb(i - startAddr, m_coils[i]);
    }

    template <typename Callback>
    void getDiscreteInputs(uint16_t startAddr, uint16_t numRegs, Callback cb) {
        throw SlaveDeviceFailure("");
    }

    template <typename Callback>
    void getHoldingRegs(uint16_t startAddr, uint16_t numRegs, Callback cb) {
        throw SlaveDeviceFailure("");
    }

    template <typename Callback>
    void getInputRegs(uint16_t startAddr, uint16_t numRegs, Callback cb) {
        throw SlaveDeviceFailure("");
    }

    void writeCoil(uint16_t addr, bool value) {
        throw SlaveDeviceFailure("");
    }

    void writeRegister(uint16_t addr, uint16_t value) {
        throw SlaveDeviceFailure("");
    }

private:
    std::vector<bool>       m_coils;
    std::vector<bool>       m_discreteInputs;
    std::vector<uint16_t>   m_holdingRegs;
    std::vector<uint16_t>   m_inputRegs;
};


ModbusGenericBackend::ModbusGenericBackend() :
    m_coils(0xFFFF),
    m_discreteInputs(0xFFFF),
    m_holdingRegs(0xFFFF),
    m_inputRegs(0xFFFF)
{}

#endif

