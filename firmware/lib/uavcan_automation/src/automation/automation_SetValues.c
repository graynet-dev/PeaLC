/*
 * UAVCAN data structure definition for libcanard.
 *
 * Autogenerated, do not edit.
 *
 */
#include "automation/SetValues.h"
#include "canard.h"

#ifndef CANARD_INTERNAL_SATURATE
#define CANARD_INTERNAL_SATURATE(x, max) ( ((x) > max) ? max : ( (-(x) > max) ? (-max) : (x) ) );
#endif

#ifndef CANARD_INTERNAL_SATURATE_UNSIGNED
#define CANARD_INTERNAL_SATURATE_UNSIGNED(x, max) ( ((x) >= max) ? max : (x) );
#endif

#if defined(__GNUC__)
# define CANARD_MAYBE_UNUSED(x) x __attribute__((unused))
#else
# define CANARD_MAYBE_UNUSED(x) x
#endif

/**
  * @brief automation_SetValues_encode_internal
  * @param source : pointer to source data struct
  * @param msg_buf: pointer to msg storage
  * @param offset: bit offset to msg storage
  * @param root_item: for detecting if TAO should be used
  * @retval returns new offset
  */
uint32_t automation_SetValues_encode_internal(automation_SetValues* source,
  void* msg_buf,
  uint32_t offset,
  uint8_t CANARD_MAYBE_UNUSED(root_item))
{
    canardEncodeScalar(msg_buf, offset, 8, (void*)&source->node_id); // 255
    offset += 8;

    canardEncodeScalar(msg_buf, offset, 8, (void*)&source->index); // 255
    offset += 8;

    // Compound
    offset = automation_Values_encode_internal(&source->values, msg_buf, offset, root_item);

    return offset;
}

/**
  * @brief automation_SetValues_encode
  * @param source : Pointer to source data struct
  * @param msg_buf: Pointer to msg storage
  * @retval returns message length as bytes
  */
uint32_t automation_SetValues_encode(automation_SetValues* source, void* msg_buf)
{
    uint32_t offset = 0;

    offset = automation_SetValues_encode_internal(source, msg_buf, offset, 1);

    return (offset + 7 ) / 8;
}

/**
  * @brief automation_SetValues_decode_internal
  * @param transfer: Pointer to CanardRxTransfer transfer
  * @param payload_len: Payload message length
  * @param dest: Pointer to destination struct
  * @param dyn_arr_buf: NULL or Pointer to memory storage to be used for dynamic arrays
  *                     automation_SetValues dyn memory will point to dyn_arr_buf memory.
  *                     NULL will ignore dynamic arrays decoding.
  * @param offset: Call with 0, bit offset to msg storage
  * @retval new offset or ERROR value if < 0
  */
int32_t automation_SetValues_decode_internal(
  const CanardRxTransfer* transfer,
  uint16_t CANARD_MAYBE_UNUSED(payload_len),
  automation_SetValues* dest,
  uint8_t** CANARD_MAYBE_UNUSED(dyn_arr_buf),
  int32_t offset)
{
    int32_t ret = 0;

    ret = canardDecodeScalar(transfer, (uint32_t)offset, 8, false, (void*)&dest->node_id);
    if (ret != 8)
    {
        goto automation_SetValues_error_exit;
    }
    offset += 8;

    ret = canardDecodeScalar(transfer, (uint32_t)offset, 8, false, (void*)&dest->index);
    if (ret != 8)
    {
        goto automation_SetValues_error_exit;
    }
    offset += 8;

    // Compound
    offset = automation_Values_decode_internal(transfer, payload_len, &dest->values, dyn_arr_buf, offset);
    if (offset < 0)
    {
        ret = offset;
        goto automation_SetValues_error_exit;
    }
    return offset;

automation_SetValues_error_exit:
    if (ret < 0)
    {
        return ret;
    }
    else
    {
        return -CANARD_ERROR_INTERNAL;
    }
}

/**
  * @brief automation_SetValues_decode
  * @param transfer: Pointer to CanardRxTransfer transfer
  * @param payload_len: Payload message length
  * @param dest: Pointer to destination struct
  * @param dyn_arr_buf: NULL or Pointer to memory storage to be used for dynamic arrays
  *                     automation_SetValues dyn memory will point to dyn_arr_buf memory.
  *                     NULL will ignore dynamic arrays decoding.
  * @retval offset or ERROR value if < 0
  */
int32_t automation_SetValues_decode(const CanardRxTransfer* transfer,
  uint16_t payload_len,
  automation_SetValues* dest,
  uint8_t** dyn_arr_buf)
{
    const int32_t offset = 0;
    int32_t ret = 0;

    // Clear the destination struct
    for (uint32_t c = 0; c < sizeof(automation_SetValues); c++)
    {
        ((uint8_t*)dest)[c] = 0x00;
    }

    ret = automation_SetValues_decode_internal(transfer, payload_len, dest, dyn_arr_buf, offset);

    return ret;
}
