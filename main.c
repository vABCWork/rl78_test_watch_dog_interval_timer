#include   "iodefine.h"
#include   "misratypes.h"
#include   "delay.h"

// INT_wdt_interval をベクタアドレス(INTWDTI=0x00004)に登録
#pragma interrupt INT_wdt_interval(vect= INTWDTI)

// ウオッチドックインターバルタイマ割り込み処理 ( 89[msec]毎 )
void INT_wdt_interval(void)
{
	
	WDTE = 0xac;	// ウオッチドック　カウンタのクリア

}

// メイン処理
// 
// ウオッチドックタイマ カウント許可
//  オーバフロー時間= 118 [ms]
//
void main(void)
{
	
	WDTIMK = 0;	// ウオッチドック インターバル・タイマ割り込みのマスクをクリア

	__EI();		// 割り込み許可
	
	while(1){
	      delay_msec(200);  // 200msec待つ
	}
	
}


