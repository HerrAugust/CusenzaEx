/*
 * Author: Agostino Mascitti <agostino690@gmail.com>
 * Copyright (c) 2015 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @file
 * @ingroup grove
 * @brief Morse interpreter using Internet example
 *
 * This project shows how to use Grove Touch or Button sensor to read a string
 * and than pass it to your computer through Internet.
 *
 * @hardware Sensors used:
 * Grove Touch (GroveTouch)
 * Grove Button (GroveButton)
 *
 * @ld -lupm-grove
 *
 * @date 24/ott/2015
 */

import java.io.*;
import java.net.*;
import java.awt.Desktop;

class ServerIntelEdison
{
   private final static int PORT = 50006;
   public static void main(String argv[]) throws Exception {
      String clientSentence = "none";
      ServerSocket IntelEdisonSocket = new ServerSocket(PORT);

      System.out.println("Waiting for the message from IntelEdison or similar board...");

      while(true)
      {
         try {
         Socket connectionSocket = IntelEdisonSocket.accept(); //wait for a new message
         System.out.println("Client connected");
         BufferedReader in = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
         while(!in.ready()) ;
         clientSentence = in.readLine();
         System.out.println("Received: " + clientSentence);

         ServerIntelEdison.say("en", clientSentence);
         System.out.println("Work done. If you want, you can send another message right now!");
         in.close();
         connectionSocket.close();
         }
         catch(Exception e) {
            System.out.println("ERROR in server");
         }
      }
   }

   //Open the default browser and makes Text To Speech of the message you sent with your Intel Edison or similar board.
   //You could be requested to insert a CATCHPA. Don't worry, it is for security.
   private static void say(String lang, String message) {
      try {
         Desktop.getDesktop().browse(new URL("http://translate.google.com/translate_tts?tl=" + lang + "&q=" + message.replaceAll(" ", "%20")).toURI());
      } catch (Exception e) {
         e.printStackTrace();
      }
   }
}
