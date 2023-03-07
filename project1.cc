// Copyright 2022 Wook-shin Han
#include <fstream>
#include <string>

#include "./project1.h"

int main(int argc, char** argv) {
  std::ifstream fin1, fin2;  // file descriptor for file1 & file2
  char arr[1000];            // arr variable read the line from file
  fin1.open(argv[2]);
  fin2.open(argv[3]);
  char* next_ptr;

  if (!strcmp(argv[1], "q1")) {
    char* zoneid;
    char* country;
    char id;
    if (fin2.is_open()) {
      while (!fin2.eof()) {
        fin2.getline(arr, 1000);
        if (arr[0] == '-') break;
      }
      fin2.getline(arr, 1000);
      while (!fin2.eof()) {
        zoneid = strtok_r(arr, " ", &next_ptr);
        id = *zoneid;
        country = strtok_r(NULL, " ", &next_ptr);
        if (!strcmp(country, "Toronto")) break;
        fin2.getline(arr, 1000);
      }

      // zoneid is succesfully stored
      /*
      what i have to do
      1. check the activation status
      2. find the matching zone id
      3. print the lastname
      */
      char* lname;
      char* active;
      char* zoneid_cmp;
      char* arr_tmp;
      if (fin1.is_open()) {
        while (!fin1.eof()) {
          fin1.getline(arr, 1000);
          if (arr[0] == '-') break;
        }
        fin1.getline(arr, 1000);

        while (!fin1.eof()) {
          // lname
          strtok_r(arr, " ", &next_ptr);
          strtok_r(NULL, " ", &next_ptr);
          lname = strtok_r(NULL, " ", &next_ptr);
          // zoneid
          arr_tmp = &arr[135];
          zoneid_cmp = strtok_r(arr_tmp, " ", &next_ptr);
          // activation status
          arr_tmp = &arr[230];
          active = strtok_r(arr_tmp, " ", &next_ptr);

          if (*zoneid_cmp == id && !strcmp(active, "1"))
            std::cout << lname << std::endl;

          fin1.getline(arr, 1000);
        }
      }
    } else {
      std::cout << "Open failed!" << std::endl;
    }
  } else if (!strcmp(argv[1], "q2")) {
    /*
    1. 바코드 순회하면서 링크드리스트 만들기
    2. 링크드리스트 구조체 멤버로는 id, cnt, next만 있으면 됨
    3. 순회다하면 cnt 2 이상인거만 추출해서 id랑 매칭되는 proddesc 출력하기
    */
    NodeList list;
    list.head = NULL;
    list.tail = NULL;
    char tmp[5];
    if (fin1.is_open()) {
      while (!fin1.eof()) {
        fin1.getline(arr, 1000);
        if (arr[0] == '-') break;
      }

      fin1.getline(arr, 1000);

      while (!fin1.eof()) {
        strtok_r(arr, " ", &next_ptr);
        for (int i = 0; i < 3; i++) {
          strncpy(tmp, strtok_r(NULL, " ", &next_ptr), 5);
        }
        Node* newnode = new Node;
        // initializing the node
        newnode->cnt = 0;
        newnode->next = NULL;
        strncpy(newnode->barcode, tmp, 5);

        insert(&list, newnode);

        fin1.getline(arr, 1000);
      }
      // print_list(&list);
      if (fin2.is_open()) {
        while (!fin2.eof()) {
          fin2.getline(arr, 1000);
          if (arr[0] == '-') break;
        }
        fin2.getline(arr, 1000);
        // maximum길이 28자
        while (!fin2.eof()) {
          char* bar_tmp;
          char prodDesc[28];
          bar_tmp = strtok_r(arr, " ", &next_ptr);
          if (is_in(&list, bar_tmp)) {
            strncpy(prodDesc, &arr[32], 28);
            prodDesc[27] = '\0';
            std::cout << bar_tmp << "                 " << prodDesc
                      << std::endl;
          }
          fin2.getline(arr, 1000);
        }
      }
    } else {
      std::cout << "Open failed!" << std::endl;
    }
  } else {
    std::cout << "Invalid input case" << std::endl;
  }
  fin1.close();
  fin2.close();
  return 0;
}
