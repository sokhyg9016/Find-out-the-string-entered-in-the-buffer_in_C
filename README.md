# Find-out-the-string-entered-in-the-buffer_in_C<br>
<hr>
<br>
<font style = "font-size: 0.9rem; color: gray;">2019. 03. 06</font>
<br>
<br>
<font style = "font-family: 'Lato',sans-serif;">이 프로젝트는 FILE 포인터로 stdin을 가리킨 상태에서 포인터를 이용하여 메모리 주소에 접근해<br>
입력한 문자열을 디버그 모드에서 확인해 보는 프로젝트입니다.</font><br>
<br>
작업 환경은 Visual Stdio 2017 이며, 2017버전은 현재(작성일) FILE 포인터의 구조체 맴버를 볼 수 없기에<br>
여러 가지 테스트를 해본 결과 '_ptr'과 '_base'등이 <br>
어떠한 위치에 있는지를 알아냈습니다.<br>
<br>
이 프로젝트에서 만든 예제는 이 두 가지 포인터를 이용하여 입력한 문자열을 확인해 보고, 정상적인 출력을 위해 문자열 끝에 NULL('\0')을 넣고 난뒤에 <br>
출력해보는 내용을 담고 있습니다.<br>
