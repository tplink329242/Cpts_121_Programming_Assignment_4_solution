#include "CppUnitTest.h"
#include "../Cpts_121_Programming_Assignment_4/PAIV_Funcions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PAIVUnitTest
{
	TEST_CLASS(PAIVUnitTest)
	{
	public:
		
		TEST_METHOD(Test_check_wager_amount)
		{
			double wager = 2.0, balance = 3.0;
			Assert::AreEqual(1, check_wager_amount(wager, balance));
			wager = 3.0;
			balance = 2.0;
			Assert::AreEqual(0, check_wager_amount(wager, balance));
		}
		TEST_METHOD(Test_calculate_sum_dice)
		{
			Assert::AreEqual(3, calculate_sum_dice(1, 2));
		}
		TEST_METHOD(Test_is_win_loss_or_point)
		{
			Assert::AreEqual(1, is_win_loss_or_point(7));
			Assert::AreEqual(0, is_win_loss_or_point(2));
			Assert::AreEqual(-1, is_win_loss_or_point(6));
		}
		TEST_METHOD(Test_is_point_loss_or_neither)
		{
			Assert::AreEqual(-1, is_point_loss_or_neither(5, 6));
			Assert::AreEqual(0, is_point_loss_or_neither(7, 6));
			Assert::AreEqual(1, is_point_loss_or_neither(6, 6));
		}
		TEST_METHOD(Test_adjust_bank_balance)
		{
			Assert::AreEqual(5500.0, adjust_bank_balance(5000, 500, 1));			
			Assert::AreEqual(4500.0, adjust_bank_balance(5000, 500, 0));
			Assert::AreEqual(5000.0, adjust_bank_balance(5000, 500, -1));
		}
		TEST_METHOD(Test_roll_die)
		{
			for (int i = 0; i < 99; ++i)
			{
				Assert::AreNotEqual(0, roll_die());
				Assert::AreNotEqual(7, roll_die());
			}			
		}
	};
}
