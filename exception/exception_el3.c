
#include <aj_types.h>
#include <io.h>
#include <exception.h>

// 示例使用方式：处理同步异常
void handle_sync_exception_el3(uint64_t *stack_pointer)
{
    trap_frame_t *context = (trap_frame_t *)stack_pointer;

    int el3_esr = read_esr_el3();

    int ec = ((el3_esr >> 26) & 0b111111);

    printf("        el1 esr: %x\n", el3_esr);
    printf("        ec: %x\n", ec);

    if (ec == 0x17)
    { // smc
        printf("            This is smc call handler\n");
        return;
    }

    for (int i = 0; i < 31; i++)
    {
        uint64_t value = context->r[i];
        printf("General-purpose register: %d, value: %x\n", i, value);
    }

    uint64_t elr_el1_value = context->elr;
    uint64_t usp_value = context->usp;
    uint64_t spsr_value = context->spsr;

    printf("usp: %x, elr: %x, spsr: %x\n", usp_value, elr_el1_value, spsr_value);

    while (1)
        ;
}

// 示例使用方式：处理 IRQ 异常
void handle_irq_exception_el3(uint64_t *stack_pointer)
{
    trap_frame_t *context = (trap_frame_t *)stack_pointer;

    uint64_t x1_value = context->r[1];
    uint64_t sp_el0_value = context->usp;

    // 在这里实现处理 IRQ 异常的代码
}

// 示例使用方式：处理无效异常
void invalid_exception_el3(uint64_t *stack_pointer, uint64_t kind, uint64_t source)
{
    trap_frame_t *context = (trap_frame_t *)stack_pointer;

    uint64_t x2_value = context->r[2];

    // 在这里实现处理无效异常的代码
}