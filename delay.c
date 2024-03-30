
#include   "misratypes.h"


#pragma inline_asm  delay_msec

//
//  N[msec] �҂֐�   (�C�����C���A�Z���u��)
// �����I���`�b�v�I�V���[�^ = 16 [MHz] 
//  1 clock = 1 / 16[MHz] = 0.0625 [usec]
//
// ����: AX = n_msec
//
// �@(RET�̓R���p�C�����ɑ}�������B)
//
void delay_msec( uint16_t n_msec )
{
	CMPW AX,#0x0000 ; AX - 0x0000
	SKNZ		; AX��0 �Ȃ�� ����SKIP
	BR    $DELAY_N_MS_EXIT

DLAY_N_MS_LOOP_1:	
	MOVW BC,AX	;  BC�� AX,  BC = n_msec
	
	MOVW AX,#0x0A66	; 1 msec���[�v�p (0x0A66 = 2662)
	
DLAY_N_MS_LOOP_2:
	
	NOP		
	
	SUBW	AX,#0x0001         ; AX = AX - 1 , 1 clock
	
	BNZ	$DLAY_N_MS_LOOP_2  ; AX��0�@�Ȃ�� Loop (����������:4 clock, �����s������:2 clock) 
	
	MOVW    AX,BC		   ; AX�� BC,  AX = n_msec
	
	SUBW	AX,#0x0001         ; AX = AX - 1 , 1 clock
	
	BNZ	$DLAY_N_MS_LOOP_1  ; AX��0�@�Ȃ�� Loop (����������:4 clock, �����s������:2 clock) 
	
DELAY_N_MS_EXIT:	
	
}




#pragma inline_asm  delay_1_msec

//
//  1[msec] �҂֐�    (�C�����C���A�Z���u��)
// �����I���`�b�v�I�V���[�^ = 16 [MHz] 
//  1 clock = 1 / 16[MHz] = 0.0625 [usec]
//
//�@(RET�̓R���p�C�����ɑ}�������B)
//
void delay_1_msec(void)
{
	MOVW AX,#0x0A66		; 0x0A66 = 2662
	
DLAY_1_MS_LOOP:
	
	NOP			; 1clock
	
	SUBW	AX,#0x0001		; AX = AX - 1 , 1 clock
	
	BNZ	$DLAY_1_MS_LOOP  ; AX��0�@�Ȃ�� Loop (����������:4 clock, �����s������:2 clock) 
	
	
}

