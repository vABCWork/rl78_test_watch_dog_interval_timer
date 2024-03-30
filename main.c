#include   "iodefine.h"
#include   "misratypes.h"
#include   "delay.h"

// INT_wdt_interval ���x�N�^�A�h���X(INTWDTI=0x00004)�ɓo�^
#pragma interrupt INT_wdt_interval(vect= INTWDTI)

// �E�I�b�`�h�b�N�C���^�[�o���^�C�}���荞�ݏ��� ( 89[msec]�� )
void INT_wdt_interval(void)
{
	
	WDTE = 0xac;	// �E�I�b�`�h�b�N�@�J�E���^�̃N���A

}

// ���C������
// 
// �E�I�b�`�h�b�N�^�C�} �J�E���g����
//  �I�[�o�t���[����= 118 [ms]
//
void main(void)
{
	
	WDTIMK = 0;	// �E�I�b�`�h�b�N �C���^�[�o���E�^�C�}���荞�݂̃}�X�N���N���A

	__EI();		// ���荞�݋���
	
	while(1){
	      delay_msec(200);  // 200msec�҂�
	}
	
}


