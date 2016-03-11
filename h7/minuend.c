            // minuend = minu, subtrahend = subt
            // minu, subt, update, and diff are all arrays
            update = minu;  
            bool swap = false;
            for(digit = 0; digit < max_digits; digit++){
               if (subt[digit] > minu[digit]){
                  update = subt;
                  subt = minu;
                  swap = true;
               }
            }
            for (digit = 0; digit < max_digits; digit++) {
               if (update[digit] < subt[digit]) {
                  update[digit] += 10;
                  i = digit + 1;
                  while (update[i] == 0) {
                     update[i] = 9;
                     i++;
                  }
                  update[i]--;
               }
               diff[digit] = update[digit] - subt[digit];
            }
            if(swap == true){
               diff[digit] = '-';
            }

            