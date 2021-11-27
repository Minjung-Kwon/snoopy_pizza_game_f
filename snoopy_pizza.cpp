#define _CRT_SECURE_NO_WARNINGS
#include <bangtal>
#include <iostream>
#include <stdio.h>
#include <time.h>


using namespace bangtal;
using namespace std;


TimerPtr timer;
float oven_time = 3.0f;


ScenePtr pizza_scene0, pizza_scene_intro, pizza_talking_scene, pizza_scene_start, pizza_scene1, pizza_win_scene, pizza_loose_scene, pizza_final_scene;


ObjectPtr clicks[2], pizza_talk[5], pizza_next[4], pizza_ok, pizza_startbutton, pizza_think, pizza_making_place, pizza_ingre_button[8];

ObjectPtr pizza_retry_button, pizza_fail_back, pizza_talkfail;

ObjectPtr pizza_good_back, pizza_talknext, pizza_good_button;

ObjectPtr pizza_bread, pizza_dough, pizza_bread2, pizza_quest[8] = { 0 }, pizza_my_ans[8] = { 0 };

ObjectPtr pizza_oven_click, pizza_oven;

ObjectPtr pizza_restart_button, pizza_gohome_button, pizza_next2_button, pizza_gohome_button1;

int pizza_qq[8] = { 0 };
int pizza_myans[8] = { 0 };

int pizza_score = 0;


//SoundPtr BGM;


void pizza_game_start();
void pizza_first();




// ���� �ʱ�ȭ
void reset_pizza2()
{
    for (int i = 0; i < 8;i++)
    {
        pizza_myans[i] = 0;
        pizza_qq[i] = 0;
    }
}




// retry ��ư. ���� �ٽ� ����. 
void pizza_fail()
{
    pizza_fail_back = Object::create("pizza_images/snoopy-pizza_fail.png", pizza_scene1, 0, 0);
    pizza_talkfail = Object::create("pizza_images/snoopy-pizza_talkfail.png", pizza_scene1, 40, 0);


    pizza_retry_button = Object::create("pizza_images/snoopy-pizza_retrybutton.png", pizza_scene1, 920, 40);
    pizza_retry_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

        pizza_game_start();
        pizza_retry_button->hide();
        pizza_fail_back->hide();
        pizza_talkfail->hide();

        return true;

    });

    reset_pizza2();

}




// next pizza ��ư. ���� �ϳ� �ϼ�! 
void pizza_good_next()
{

    pizza_good_back = Object::create("pizza_images/snoopy-pizza_good.png", pizza_scene1, 0, 0);
    pizza_talknext = Object::create("pizza_images/snoopy-pizza_talknext.png", pizza_scene1, 40, 0);

    pizza_good_button = Object::create("pizza_images/snoopy-pizza_nextpizzabutton.png", pizza_scene1, 920, 40);
    pizza_good_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

        pizza_game_start();
        pizza_good_button->hide();
        pizza_good_back->hide();
        pizza_talknext->hide();

        return true;
    });

    reset_pizza2();


}






// ���� ���� ���� �ջ���� ! (� ��������� !)
void pizza_game_score()
{

    char path[50];
    sprintf(path, "pizza_images/snoopy-pizza_%d.png", pizza_score);
    

    if (pizza_score >= 5)   //���� 5�� �̻� ����� ���!
    {
        // win ȭ��
        // ��� �¾Ҵ��� �׸����� ���!
        pizza_win_scene->enter();

        auto pizza_score_image = Object::create(path, pizza_win_scene, 700, 235);


        pizza_next2_button = Object::create("pizza_images/snoopy-pizza_next2.png", pizza_win_scene, 810, 60);
        pizza_next2_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

            // ���̳� ��� �̵�
            pizza_final_scene->enter();

            pizza_gohome_button1 = Object::create("pizza_images/snoopy-pizza_homebutton.png", pizza_final_scene, 950, 50);
            pizza_gohome_button1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {


                /*
                 *  ������ ���� ��ü ���� ȭ�� �̵�
                 */


                return true;
            });


            return true;
        });
        
    }
    else
    {
        // loose ȭ��
        pizza_loose_scene->enter();

        
        auto pizza_score_image = Object::create(path, pizza_loose_scene, 700, 235);



        pizza_restart_button = Object::create("pizza_images/snoopy-pizza_restartbutton.png", pizza_loose_scene, 520, 60);
        pizza_gohome_button = Object::create("pizza_images/snoopy-pizza_homebutton.png", pizza_loose_scene, 820, 60);



        pizza_restart_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

            pizza_first();
            pizza_scene0->enter();

            pizza_restart_button->hide();
            pizza_gohome_button->hide();


            return true;
        });

        pizza_gohome_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {


            /*
             *  ������ ���� ��ü ���� ȭ�� �̵�
             */


            return true;
        });

    }

    pizza_score = 0;
    reset_pizza2();


}





// ���� ���� ���� �ð� �����ִ� Ÿ�̸� clock.
void pizza_show_clock()
{


    auto clock = Timer::create(60.f);
    showTimer(clock);
    clock->start();


    // ���� ��� ������� �Ѿ !!

    clock->setOnTimerCallback([&](TimerPtr clock)->bool {

        
        pizza_game_score();


        return true;
    });

}





// ���� ����. ���� ��������!
void pizza_question() {


    auto think = Object::create("pizza_images/snoopy-pizza_think.png", pizza_scene1, 870, 300);

    //���� ����. ������ �ʿ�
    pizza_bread = Object::create("pizza_images/pizza00.png", pizza_scene1, 980, 450);
    pizza_bread->setScale(0.5f);


    //�丶�� �ҽ� ����. 3���� 2�� Ȯ���� �ҽ��� ���´�.
    int num0;
    num0 = rand() % 3;
    if (num0 != 1)
    {
        pizza_qq[0] = 1;
        pizza_quest[0] = Object::create("pizza_images/pizza0.png", pizza_scene1, 980, 450);
        pizza_quest[0]->setScale(0.5f);
    }


    // ���� ����. 3���� 1�� Ȯ���� ���´�.
    int num1;
    num1 = rand() % 3;
    if (num1 == 1)
    {
        pizza_qq[1] = 1;
        pizza_quest[1] = Object::create("pizza_images/pizza1.png", pizza_scene1, 980, 450);
        pizza_quest[1]->setScale(0.5f);
    }


    // �Ǹ� ����. 4���� 1�� Ȯ���� ���´�.
    int num2;
    num2 = rand() % 3;
    if (num2 == 1)
    {
        pizza_qq[2] = 1;
        pizza_quest[2] = Object::create("pizza_images/pizza2.png", pizza_scene1, 980, 450);
        pizza_quest[2]->setScale(0.5f);
    }


    // �� ����. 2���� 1�� Ȯ���� ���´�.
    int num3;
    num3 = rand() % 4;
    if (num3 == 1)
    {
        pizza_qq[3] = 1;
        pizza_quest[3] = Object::create("pizza_images/pizza3.png", pizza_scene1, 980, 450);
        pizza_quest[3]->setScale(0.5f);
    }


    // ���ξ��� ����. 5���� 1�� Ȯ���� ���´�.
    int num4;
    num4 = rand() % 5;
    if (num4 == 1)
    {
        pizza_qq[4] = 1;
        pizza_quest[4] = Object::create("pizza_images/pizza4.png", pizza_scene1, 980, 450);
        pizza_quest[4]->setScale(0.5f);

    }


    // �ø��� ����. 2���� 1�� Ȯ���� ���´�.
    int num5;
    num5 = rand() % 2;
    if (num5 == 1)
    {
        pizza_qq[5] = 1;
        pizza_quest[5] = Object::create("pizza_images/pizza5.png", pizza_scene1, 980, 450);
        pizza_quest[5]->setScale(0.5f);

    }


    // ���� ����. 5���� 1�� Ȯ���� ���´�.
    int num6;
    num6 = rand() % 5;
    if (num6 == 1)
    {
        pizza_qq[6] = 1;
        pizza_quest[6] = Object::create("pizza_images/pizza6.png", pizza_scene1, 980, 450);
        pizza_quest[6]->setScale(0.5f);

    }


    // ġ�� ����. 3���� 2�� Ȯ���� ���´�.
    int num7;
    num7 = rand() % 3;
    if (num7 != 1)
    {
        pizza_qq[7] = 1;
        pizza_quest[7] = Object::create("pizza_images/pizza7.png", pizza_scene1, 980, 450);
        pizza_quest[7]->setScale(0.5f);

    }

}





// ��� ���� ��ư ����. 
void pizza_ingre_click()
{

    int y = 0;
    int count = 1;

    for (int i = 0; i < 8;i++)
    {

        pizza_ingre_button[i] = Object::create("pizza_images/pizza_choose.png", pizza_scene1, 337 + (i % 4) * 131, 572 - y);
        count++;

        if (count == 5)
        {
            y += 98;
        }
    }

}





// ���� ��ư ����
void  pizza_pick_answer()
{

    pizza_ingre_click();


    pizza_my_ans[0] = Object::create("pizza_images/pizza0.png", pizza_scene1, 400, 50);
    pizza_my_ans[1] = Object::create("pizza_images/pizza1.png", pizza_scene1, 400, 50);
    pizza_my_ans[2] = Object::create("pizza_images/pizza2.png", pizza_scene1, 400, 50);
    pizza_my_ans[3] = Object::create("pizza_images/pizza3.png", pizza_scene1, 400, 50);
    pizza_my_ans[4] = Object::create("pizza_images/pizza4.png", pizza_scene1, 400, 50);
    pizza_my_ans[5] = Object::create("pizza_images/pizza5.png", pizza_scene1, 400, 50);
    pizza_my_ans[6] = Object::create("pizza_images/pizza6.png", pizza_scene1, 400, 50);
    pizza_my_ans[7] = Object::create("pizza_images/pizza7.png", pizza_scene1, 400, 50);

    pizza_my_ans[0]->hide();
    pizza_my_ans[1]->hide();
    pizza_my_ans[2]->hide();
    pizza_my_ans[3]->hide();
    pizza_my_ans[4]->hide();
    pizza_my_ans[5]->hide();
    pizza_my_ans[6]->hide();
    pizza_my_ans[7]->hide();

    // �丶�� �ҽ� ����
    pizza_ingre_button[0]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

        pizza_my_ans[0]->show();
        pizza_myans[0] = 1;


        return true;
    });

    // ���� ����
    pizza_ingre_button[1]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

        pizza_my_ans[1]->show();
        pizza_myans[1] = 1;


        return true;
    });

    // �Ǹ� ����
    pizza_ingre_button[2]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

        pizza_my_ans[2]->show();
        pizza_myans[2] = 1;


        return true;
    });


    // �� ����
    pizza_ingre_button[3]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

        pizza_my_ans[3]->show();
        pizza_myans[3] = 1;

        return true;
    });


    // ���ξ��� ����
    pizza_ingre_button[4]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

        pizza_my_ans[4]->show();
        pizza_myans[4] = 1;


        return true;
    });


    // �ø��� ����
    pizza_ingre_button[5]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

        pizza_my_ans[5]->show();
        pizza_myans[5] = 1;


        return true;
    });


    // ���� ����
    pizza_ingre_button[6]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

        pizza_my_ans[6]->show();
        pizza_myans[6] = 1;


        return true;
    });


    // ġ�� ����
    pizza_ingre_button[7]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

        pizza_my_ans[7]->show();
        pizza_myans[7] = 1;


        return true;
    });


}




// ����� ���� �� �迭 Ȯ�� �۾�
bool check_good()
{
    for (int i = 0; i < 8; i++)
    {
        if (pizza_qq[i] != pizza_myans[i])
        {
            return false;
        }
    }
    return true;
}





// 05 ���� ���� ����. 
void pizza_game_start()
{

    pizza_scene1->enter();

    auto snoopy_cook = Object::create("pizza_images/snoopy-cook.png", pizza_scene1, 25, 0);
    snoopy_cook->setScale(0.8f);

    pizza_making_place = Object::create("pizza_images/snoopy-pizza_making.png", pizza_scene1, 337, 0);


    pizza_question();


    //���� ����. �̰� ������ ���� ��� �ֱⰡ ������.
    pizza_dough = Object::create("pizza_images/pizza000.png", pizza_scene1, 400, 50);
    pizza_bread2 = Object::create("pizza_images/pizza00.png", pizza_scene1, 400, 50);
    pizza_bread2->hide();

    //���� ��� �����ϱ� (���� ����)
    pizza_dough->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

        pizza_bread2->show();
        pizza_dough->hide();

        pizza_pick_answer();

        return true;
    });





    //���쿡 ����
    bool ovencheck = false;

    timer = Timer::create(oven_time);   //���� Ÿ�̸�
    timer->setOnTimerCallback([&](auto)->bool
    {
        pizza_oven->hide();

        //������ �Ϸ�Ǹ� ������ Ȯ���غ���
        if (ovencheck)
        {
            if (check_good())
            {
                pizza_good_next();
                pizza_score += 1;
            }
            else
            {
                pizza_fail();
            }

        }

        return 0;
    });



    pizza_oven = Object::create("pizza_images/pizza_oven.png", pizza_scene1, 337, 0);
    pizza_oven->hide();

    pizza_oven_click = Object::create("pizza_images/pizza_oven_click.png", pizza_scene1, 110, 280);
    pizza_oven_click->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

        ovencheck = true;
        pizza_oven->show();
        timer->set(oven_time);
        timer->start();

        return true;
    });



}




// 04 �ֹ� 1. ������ ������ ��ȭ ����. 
void pizza_kitchen()
{


    pizza_talking_scene->enter();

    pizza_talk[0] = Object::create("pizza_images/snoopy-pizza_talk1.png", pizza_talking_scene, 40, 0);
    pizza_talk[1] = Object::create("pizza_images/snoopy-pizza_talk2.png", pizza_talking_scene, 40, 0);
    pizza_talk[2] = Object::create("pizza_images/snoopy-pizza_talk3.png", pizza_talking_scene, 40, 0);
    pizza_talk[3] = Object::create("pizza_images/snoopy-pizza_talk4.png", pizza_talking_scene, 40, 0);
    pizza_talk[4] = Object::create("pizza_images/snoopy-pizza_talk5.png", pizza_talking_scene, 40, 0);

    pizza_talk[1]->hide();
    pizza_talk[2]->hide();
    pizza_talk[3]->hide();
    pizza_talk[4]->hide();

    pizza_next[0] = Object::create("pizza_images/snoopy-pizza_next.png", pizza_talking_scene, 940, 40);
    pizza_next[1] = Object::create("pizza_images/snoopy-pizza_next.png", pizza_talking_scene, 940, 40);
    pizza_next[2] = Object::create("pizza_images/snoopy-pizza_next.png", pizza_talking_scene, 940, 40);
    pizza_next[3] = Object::create("pizza_images/snoopy-pizza_next.png", pizza_talking_scene, 940, 40);
    pizza_ok = Object::create("pizza_images/snoopy-pizza_ok.png", pizza_talking_scene, 940, 40);

    pizza_next[1]->hide();
    pizza_next[2]->hide();
    pizza_next[3]->hide();
    pizza_ok->hide();


    pizza_next[0]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

        pizza_talk[0]->hide();
        pizza_next[0]->hide();
        pizza_talk[1]->show();
        pizza_next[1]->show();
        return true;
    });

    pizza_next[1]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

        pizza_talk[1]->hide();
        pizza_next[1]->hide();
        pizza_talk[2]->show();
        pizza_next[2]->show();
        return true;
    });

    pizza_next[2]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

        pizza_talk[2]->hide();
        pizza_next[2]->hide();
        pizza_talk[3]->show();
        pizza_next[3]->show();
        return true;
    });

    pizza_next[3]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

        pizza_talk[3]->hide();
        pizza_next[3]->hide();
        pizza_talk[4]->show();
        pizza_ok->show();
        return true;
    });

    pizza_ok->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

        pizza_talk[4]->hide();
        pizza_ok->hide();

        pizza_show_clock();     // ���� Ÿ�̸� ���� !
        pizza_game_start();     // ���� ���� ���� !

        return true;
    });

}



// 03 start ��ư. ��¥ ���� ����
void pizza_start()
{

    pizza_scene_start->enter();
    pizza_startbutton = Object::create("pizza_images/snoopy-startbutton.png", pizza_scene_start, 500, 60);

    pizza_startbutton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

        pizza_kitchen();
        return true;
    });

}



// 02 ���� ��Ʈ�� ȭ��(���� ����)
void pizza_intro()
{

    
    pizza_scene_intro->enter();
    clicks[1] = Object::create("pizza_images/pizza_click.png", pizza_scene_intro, 0, 0);  //ȭ�� Ŭ��
    clicks[1]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        clicks[1]->hide();
        pizza_start();
        return true;
    });

}





// 01 ���� ���� ȭ�� 
void pizza_first()
{
    clicks[0] = Object::create("pizza_images/pizza_click.png", pizza_scene0, 0, 0);  //ȭ�� Ŭ��
    clicks[0]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        clicks[0]->hide();
        pizza_intro();
        return true;
    });

}




int main()
{
    srand((unsigned int)time(NULL));

    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);



    pizza_scene0 = Scene::create("snoopy_pizza game", "pizza_images/snoopy-pizza_start.png");   //���� ���� ȭ��
    pizza_scene_intro = Scene::create("snoopy_pizza game", "pizza_images/snoopy-pizza_intro.png"); //���� ����
    pizza_scene_start = Scene::create("snoopy_pizza game", "pizza_images/snoopy-pizza_backgound.png"); // ���� ��ư �ִ� ȭ��
    pizza_talking_scene = Scene::create("", "pizza_images/snoopy-pizza_kitchen.png"); //��ȭ ���
    pizza_scene1 = Scene::create("", "pizza_images/snoopy-pizza_kitchen.png"); //�ֹ�1
    pizza_win_scene = Scene::create("", "pizza_images/snoopy-pizza_win.png"); //win ���
    pizza_loose_scene = Scene::create("", "pizza_images/snoopy-pizza_loose.png"); //win ���
    pizza_final_scene = Scene::create("", "pizza_images/snoopy-pizza_outro.png"); //���̳� ���




    pizza_first();



    startGame(pizza_scene0);
    return 0;
}