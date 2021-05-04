#include "Reader.h"

voice startingVoice(0, 3.0);

voice oneDigits[9] = {//אחד, שתיים, שלוש וכו'
  voice(1, 2.0),
  voice(2, 2.0),
  voice(3, 2.0),
  voice(4, 2.0),
  voice(5, 2.0),
  voice(6, 2.0),
  voice(7, 2.0),
  voice(8, 2.0),
  voice(9, 2.0)
};

voice towDigits[9] = {
  voice(10, 3.3),
  voice(11, 3.0),
  voice(12, 3.2),
  voice(13, 3.0),
  voice(14, 3.0),
  voice(15, 3.0),
  voice(16, 3.0),
  voice(17, 3.0),
  voice(18, 3.0)
};

voice threeDigits[9] = { // מאה, מאתיים, שלושמאות וכו'
  voice(19, 3.0),
  voice(20, 3.0),
  voice(21, 3.0),
  voice(22, 3.0),
  voice(23, 3.0),
  voice(24, 3.0),
  voice(25, 3.0),
  voice(26, 3.0),
  voice(27, 3.0)
};

voice fourDigits[9] = { // אלף, אלפיים, שלושתאלפים וכו'
  voice(28, 3.0),
  voice(29, 3.0),
  voice(30, 3.0),
  voice(31, 3.0),
  voice(32, 3.0),
  voice(33, 3.0),
  voice(34, 3.0),
  voice(35, 3.0),
  voice(36, 3.0)
};

voice months[12] = { // אלף, אלפיים, שלושתאלפים וכו'
  voice(37, 3.0),
  voice(38, 3.0),
  voice(39, 3.0),
  voice(40, 3.0),
  voice(41, 3.0),
  voice(42, 3.0),
  voice(43, 3.0),
  voice(44, 3.0),
  voice(45, 3.0),
  voice(46, 3.0),
  voice(47, 3.0),
  voice(48, 3.0)
};

voice CountingNumberOneDigits[9] = {//אחד, שתיים, שלוש וכו'
  voice(49, 2.0),
  voice(50, 2.0),
  voice(51, 2.0),
  voice(52, 2.0),
  voice(53, 2.0),
  voice(54, 2.0),
  voice(55, 2.0),
  voice(56, 2.0),
  voice(57, 2.0)
};

voice vav(58, 0.8);
voice haiom(59, 0.9);
voice iomLagomerShehem(60, 3.0);
voice lagomer(61, 1.0);
voice hashah(62, 1.0);
voice esreh(63, 1.0);
voice ve(64, 0.3); //וו החיבור, כמו עשרים ו*אחת
voice ha(65, 0.3); // הא הידיעה
voice beh(66, 0.3); //בית כמו שלוש *ב*אפריל

Reader::Reader(int TX, int RX): SOS(TX, RX)
{
  Serial.begin(9600);
  Serial.println("meking reader");
  delay(1000000);
  SOS.begin(9600);
  //Player.begin(SOS);
  if (Player.begin(SOS))
  {
    Serial.println("MP3 player started");
  }
  else
  {
    Serial.println("eror actevating MP3 player");
  }
  Player.volume(30);
}

void Reader::Say(TimePoint now)
{
  /*
     דוגמא לאיך אמירה אמורה להיות:
  ***זה מה שעושים   * השעה אחת שלושים ושש, היום העשרים ושניים באפריל*
     היום עשרים וארבעה יום לגומר שהם שלושה שבועות ושלושה ימים לגומר
     נותרו עוד מאה ושמונה עשרה ימים, עשרים ושתים שעות, ארבע עשרה דקות ושלושים ושלוש שניות.
  */
  play(hashah);
  now.hour = now.hour % 12;
  if (now.hour == 0)
  {
    now.hour = 12;
  }
  play2digits(now.hour);
  play2digits(now.minute);
  delay(500);
  play(haiom);
  play(ha);
  play2digits(now.day);
  play(beh);
  play(months[now.month - 1]);
}

void Reader::play(voice Voice)
{
  Player.play(Voice.ID());
  delay(Voice.Duration() * 1000);
}

void Reader::play2digits(int number)
{
  if (number == 0)
    /*dont play*/ return;

  if (number < 10)
    play(CountingNumberOneDigits[number - 1]); return;

  if (number == 10)
    play(towDigits[0]); return;

  int theTensDigit = 10 * floor(number / 10);
  int theOnesDigit = number - theTensDigit;

  if (number < 20)
  {
    play(oneDigits[theOnesDigit - 1]);
    play(esreh);
    return;
  }

  if (number < 100)
  {
    play(towDigits[theTensDigit - 1]);
    play(ve);
    play(oneDigits[theOnesDigit - 1]);
    return;
  }
}
