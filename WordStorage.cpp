#include "WordStorage.h"

WordStorage::WordStorage()
{
	wordlist.clear();

	init();

	srand((unsigned)time(NULL));
}

WordStorage::~WordStorage()
{

}

Word* WordStorage::getRandWord(int stage)
{
	int r = rand() % wordlist.size();

	while (wordlist.at(r)->getType()!=stage)
	{
		r = rand() % wordlist.size();
	}

	return wordlist.at(r);
}

void WordStorage::init()
{

	wordlist.push_back(new Word("pen2*cil1", "연필", 0));
	wordlist.push_back(new Word("com2*pass1", "컴퍼스", 0));
	wordlist.push_back(new Word("pa2*per1", "종이", 0));
	wordlist.push_back(new Word("tack2", "압정", 0));
	wordlist.push_back(new Word("stick2*er1", "스티커", 0));

	//wordlist.push_back(new Word("dust2*er1", "먼지털이", 1));
	//wordlist.push_back(new Word("gar2*bage1", "쓰레기", 1));
	//wordlist.push_back(new Word("pol2*ish1", "광택제", 1));
	//wordlist.push_back(new Word("va2*cuum1", "진공청소기", 1));
	wordlist.push_back(new Word("wipe2", "닦다", 1));

	wordlist.push_back(new Word("dust2", "먼지", 2));
	wordlist.push_back(new Word("scrub2", "스크럽", 2));
	wordlist.push_back(new Word("stain2", "얼룩", 2));
	wordlist.push_back(new Word("clean2*er1", "세정제", 2));
	wordlist.push_back(new Word("plun2*ger1", "플런저", 2));

	wordlist.push_back(new Word("boil2", "끓이다", 3));
	wordlist.push_back(new Word("pic2*kle1", "피클", 3));
	wordlist.push_back(new Word("steam2", "증기", 3));
	wordlist.push_back(new Word("scale2", "저울", 3));
	wordlist.push_back(new Word("pot2", "냄비", 3));

	wordlist.push_back(new Word("ket2*tle1", "주전자", 4));
	wordlist.push_back(new Word("chop2*sticks1", "젓가락", 4));
	wordlist.push_back(new Word("knife2", "칼", 4));
	wordlist.push_back(new Word("spoon2", "숟가락", 4));
	wordlist.push_back(new Word("fun2*nel1", "깔때기", 4));

	wordlist.push_back(new Word("eel2", "뱀장어", 5));
	wordlist.push_back(new Word("squid2", "오징어", 5));
	wordlist.push_back(new Word("ca2*vi1*ar2", "캐비어", 5));
	wordlist.push_back(new Word("kelp2", "해초", 5));
	wordlist.push_back(new Word("oys2*ter1", "굴", 5));

	wordlist.push_back(new Word("sal2*mon1", "연어", 6));
	wordlist.push_back(new Word("shrimp2", "새우", 6));
	wordlist.push_back(new Word("shark2", "상어", 6));
	wordlist.push_back(new Word("oc2*to1*pus1", "문어", 6));
	wordlist.push_back(new Word("tu2*na1", "참치", 6));

	wordlist.push_back(new Word("a2*pri1*cot2", "살구", 7));
	wordlist.push_back(new Word("straw2*berry2", "딸기", 7));
	wordlist.push_back(new Word("or2*ange1", "오렌지", 7));
	wordlist.push_back(new Word("per1*sim2*mon1", "감", 7));
	wordlist.push_back(new Word("gua2*va1", "구아바", 7));

	wordlist.push_back(new Word("cher2*ry1", "체리", 8));
	wordlist.push_back(new Word("plum2", "자두", 8));
	wordlist.push_back(new Word("ba1*na2*na1", "바나나", 8));
	wordlist.push_back(new Word("pa1*pa2*ya1", "파파야", 8));
	wordlist.push_back(new Word("grape2", "포도", 8));

	wordlist.push_back(new Word("sub2*ject1", "과목", 9));
	wordlist.push_back(new Word("En2*glish1", "영어", 9));
	wordlist.push_back(new Word("math2", "수학", 9));
	wordlist.push_back(new Word("science2", "과학", 9));
	wordlist.push_back(new Word("his2*to1*ry1", "역사", 9));

	wordlist.push_back(new Word("lib2*ra1*ry1", "도서관", 10));
	wordlist.push_back(new Word("text2*book2", "교과서", 10));
	wordlist.push_back(new Word("stu2*dent1", "학생", 10));
	wordlist.push_back(new Word("tea2*cher1", "선생", 10));
	wordlist.push_back(new Word("u2*ni1*form1", "교복, 유니폼", 10));

	//

	wordlist.push_back(new Word("throat2", "목구멍", 11));
	wordlist.push_back(new Word("shoul2*der1", "어께", 11));
	wordlist.push_back(new Word("back2*bone1", "등뼈", 11));
	wordlist.push_back(new Word("arm2*pit1", "겨드랑이", 11));
	wordlist.push_back(new Word("tounge2", "혀", 11));

	wordlist.push_back(new Word("arm2", "팔", 12));
	wordlist.push_back(new Word("toe2*nail1", "발톱", 12));
	wordlist.push_back(new Word("el2*bow1", "팔꿈치", 12));
	wordlist.push_back(new Word("knuc2*kle1", "무릎관절", 12));
	wordlist.push_back(new Word("an2*kle1", "발목", 12));

	wordlist.push_back(new Word("cloth2", "옷", 13));
	wordlist.push_back(new Word("ca1*su2*al11", "평상복", 13));
	wordlist.push_back(new Word("tux1*e2*do1", "턱시도", 13));
	wordlist.push_back(new Word("u2*ni1*form1", "유니폼", 13));
	wordlist.push_back(new Word("jac2*ket1", "재킷", 13));

	wordlist.push_back(new Word("under2*wear2", "속옷", 14));
	wordlist.push_back(new Word("pa1*ja2*mas1", "잠옷", 14));
	wordlist.push_back(new Word("slip2*pers1", "슬리퍼", 14));
	wordlist.push_back(new Word("sneak2*ers1", "운동화", 14));
	wordlist.push_back(new Word("bea2*nie1", "비니", 14));

	wordlist.push_back(new Word("jewel2*ry1", "보석", 15));
	wordlist.push_back(new Word("ear2*rings1", "귀걸이", 15));
	wordlist.push_back(new Word("gloves2", "장갑", 15));
	wordlist.push_back(new Word("wal2*let1", "지갑", 15));
	wordlist.push_back(new Word("clutch2", "클러치", 15));

	wordlist.push_back(new Word("soap2", "비누", 16));
	wordlist.push_back(new Word("lo2*tion1", "로션", 16));
	wordlist.push_back(new Word("sham1*poo2", "샴푸", 16));
	wordlist.push_back(new Word("to2*ner1", "토너", 16));
	wordlist.push_back(new Word("sun2*block1", "썬크림", 16));




}