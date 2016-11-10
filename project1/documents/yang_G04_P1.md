##Title of Project
###Author Names
###黄智忠
####Date: 2016-10-17
-----
####Chapter 1:  Introduction 
* 本实验用C++实现,以MFC构建了一个拥有非常直观的用户交互界面的计算器，用户可以不断输入表达式进行计算,AC键清屏进行一次新的运算;退出键退出程序.
* 用户可以从键盘输入，也可以从鼠标输入表达式, 计算器上有三个文本框:
    * 实时显示用户输入的表达式
    * 当用户按下=号时的计算结果
    * 表达式转化成的后缀表达式.
* 栈的基本操作由自己实现.
* 通过对中缀表达式转换成后缀表达式,然后对后缀表达式计算
* 计算器输入的表达式输入的表达式中可以有整数、实数、括号，运算符包括+、-、*、/（包括单目负）.
* **这个计算器还支持很多其他的操作:** 
    1. 支持十进制,二进制,十六进制计算
    2. 支持三角函数,幂,阶乘,取余,以e为底和以10为底的对数.

-----
####Chapter 2:  Algorithm Specification 
Description of all the algorithms involved for solving the problem, including specifications of main data structures.   

* **主要数据结构设计说明代码和文字说明**
    * 链表和栈的实现,计算机的实现只要用到栈的pop(),push(),length()两个成员函数,作用分别是弹栈,压栈,返回栈的长度,如下:
```C++
template <typename E> class Link{
    private:
    public  :
        E element;
        Link *next;
        Link(E ele, Link *nex)
        {
            element = ele;
            next = nex;
        }
};
template <typename E> class SList{
    private:
        Link<E> *top;
        int size;
    public:
        SList(){
            top = NULL;
            size = 0;
        }

        void clear(){
            while(top != NULL){
                Link<E>* temp = top;
                top = top-> next;
                delete temp;
            }
            size = 0;
        }

        void push(E it){
            top = new Link<E>(it,top);
            size++;
        }

        E pop(){
            if(top ==NULL){
                printf("Error! --- Is empty!");
                return 0;
            }
            Link<E>* temp;
            E it = top->element;
            temp = top->next;
            delete top;
            top = temp;
            size--;
            return it;
        }

        E topValue(){
            if(top ==NULL)
            {
                return 0;
            }
            return top->element;
        }

        int length(){
            return size;
        }
};
```
    * 由MFC自动生成的控件
* **系统设计思想:**
    * 程序GUI元素由MFC自动生成，用于与用户交互
    * 系统的主要模块结构及各模块关系:
    ```C++
    //type 进制数，1:十进制，2:二进制，3:十六进制
    int type;
    //求阶乘
    int factorial(int num);
    //array为操作数，讲十六进制转为十进制
    int hexToDecimal(char *array);
    //array为操作数，讲二进制转为十进制
    int binaryToDecimal(char *array); 
    //得到操作符的优先级
    int priority(char op); 
    //将numS中以char存储的操作数转化为double并压入num栈中以进行计算
    void pushNum(SList<char> *numS,SList<double> *num);
    //out 后缀表达式,maxNum 数组长度,后缀表达式求值，返回求值据结果
    double calculate(char *out , int maxNum); 
    //从GUI获得用户输出，转化为后缀表达式并计算
    void CCalculatorDlg::OnCALCU();
    ```
        * 各模块关系
        ![](http://ww4.sinaimg.cn/large/006y8lVagw1f91g3l6unuj30ta0dsaao.jpg)
        * 各模块结构
        #####CCalculatorDlg::OnCALCU()模块的结构：
        获得用户输入的中缀表达式，并将其存了char型数组array中:
        ```C++
        CString str;
        GetDlgItem(EDIT)->GetWindowText(str);
        char *array = new char[100];
        array = (char *) str.GetBuffer(0);
        ```
        一次从左到右遍历这个中缀表达式: 
        ```C++
        while(array[i] != '\0')
        ```
        定义out为存储转化的后缀表达式的数组：
        ```C++
        char out[100];
        ```
        定义中间栈**temp**保存操作符：
        ```C++
        SList<char> temp;
        ```
        当array中的元素为操作数时，则将其直接压入out中，其中j是后缀表达式out的坐标，用来遍历。例如：
        ```C++
        if((array[i] >= '0' &&array[i] <= '9')||array[i] == '.' ||array[i] == '^'||(array[i] >='a'&&array[i] <='z'||array[i] == '!')){
            out[j] = array[i];
            j++;
        }
        ```
        当array中的元素为左括号（时，不丢弃也压入out和temp中，这点不同于其他中缀转后缀，因为需要处理单目负，右括号直接丢弃，并依次将temp中的运算符弹入out中知道遇到了左括号，左后将temp中的左括号丢弃。如下：
        ```C++
                else if(array[i] == '('){
            out[j++] = '(';
            temp.push(array[i]);
        }
        else if(array[i] == ')'){
            //优先输出结果
            while(temp.topValue() != '(')
            {
                out[j++] = temp.pop();
            }
            temp.pop();
        }
        ```
        其他操作符则调用priority，temp为空或着优先级高于temp栈顶的元素，则直接压入temp，否则将temp栈顶元素弹出并压入out中.同时压入一个空格以隔开操作数和运算符.代码如下：
        ```C++
        else if(array[i] == '+'||array[i] == '-'||array[i] == '*'||array[i] == '/'||array[i] == '%')
        {
            //遇到运算符是用空格隔开以处理操作数
            out[j++] = ' ';
            //按操作符优先级入栈
            while(priority(array[i]) <= priority(temp.topValue()) )
            {
                out[j++] = temp.pop();
            }
            temp.push(array[i]);
        }
        ```
        扫描完毕后将temp中剩余的运算符压入out，最终转化成了有左括号和空格隔开的后缀表达式:
        ```C++
        //将temp中剩余运算符入栈
        while(temp.length() != 0)
        {
            out[j++] = temp.pop();
        }
        ```
        最后对用户在GUI中选择的不同进制，type=1 十进制，type=2 二进制，type=3 十六进制，依次处理。如果是十进制则直接调研calculate模块进行计算,如果是二进制或十六进制则分别调用calculate计算后得到的十进制结果用itoa函数转化为相应的进制，最后格式化输出到界面上：
        ```C++
        //十进制后缀表达式求值
        maxNum = j;
        char *buf = new char[50];
        if(type == 1)
        {
            sprintf(buf, "%.3lf\n", calculate(out,maxNum));
            GetDlgItem(OUTPUT)->SetWindowText(buf);
        }
        //二进制后缀表达式求值
        if(type == 2)
        {
            itoa(calculate(out,maxNum), buf , 2);
            GetDlgItem(OUTPUT)->SetWindowText(buf);
        }
        //十六进制表达式求值
        if(type == 3)
        {
            itoa(calculate(out,maxNum), buf , 16);
            GetDlgItem(OUTPUT)->SetWindowText(buf);
        }
        GetDlgItem(expression)->SetWindowText(express);
        ```
        ####calculate模块的结构：
        函数声明：
        ```C++
        //out 后缀表达式
        //maxNum 数组长度
        double calculate(char *out, int maxNum);
        ```
        从左往右扫描out即后缀表达式，如果是操作数则压入char型的栈numS中，如下：
        ```C++
        if(out[j] >= '0' && out[j] <='9' || out[j] == '.' ||out[j] =='^'||(out[j] >='a'&&out[j] <='z')||out[j] =='!')
        {
            numS.push(out[j]);
        }
        ```
        如果遇到一个左括号，则压入一个极大的数到double型栈num,以处理单目负：
        ```C++
        if(out[j] == '(')
        {
            //?
            num.push(999999);
        }
        ```
        如果遇到空格则将numS中的操作数转化成double然后压入到num中得到真正的操作数：
        ```C++
        if(out[j] == ' ')
        {
            pushNum(&numS,&num);
        }
        ```
        其他操作符先将numS中的操作数转化成double然后压入到num，然后弹出num中的数进行计算并最终将结果重新压入num：
        ```C++
        f (out[j] == '+')
        {
            //计算加号，讲numS中的数字压入num并弹出num中的两个操作数计算后压栈
            pushNum(&numS,&num);
            x2 = num.pop();
            x1 = num.pop();
            //?
            if(x1 == 999999){
                x1 = num.pop();
            }
            num.push(x1+x2);
        }  
        if (out[j] =='-')  
        {
            //计算减号
            pushNum(&numS,&num);
            x2 = num.pop();  
            x1 = num.pop();  
            if(x1 == 999999)
            {
                num.push((-1)*x2);
            }
            if(x1 != 999999)
            {
                num.push(x1 - x2);
            }
        } 
        if (out[j] =='*')  
        {  
            pushNum(&numS,&num);
            x2 = num.pop();  
            x1 = num.pop();  
            if(x1 == 999999){
                x1 = num.pop();
            }
            num.push(x1*x2);   
        } 
        if (out[j] =='/')  
        {  
            pushNum(&numS,&num);
            x2 = num.pop();  
            x1 = num.pop(); 
            if(x1 == 999999){
                x1 = num.pop();
            }
            num.push(x1/x2);   
        } 
        //执行求余操作
        if (out[j] =='%')  
        {  
            pushNum(&numS,&num);
            x2 = num.pop();  
            x1 = num.pop(); 
            if(x1 == 999999){
                x1 = num.pop();
            }
            num.push((int)x1%(int)x2);   
        } 
        ```
        最后返回计算结果给CCalculatorDlg::OnCALCU()模块。
        ####pushNum模块结构：
        函数声明：
        ```C++
        //将压入栈numS中的字符转换为操作数压入栈num中
        void pushNum(SList<char> *numS,SList<double> *num);
        ```
        bool类型来表明numS中的字符是否有单目运算符，如果有的话则为真，否则为非，最后计算后将结果压入num中，tempNum为操作数：
        ```C++
        bool isMul = false;
        bool isFactorial = false;
        bool isSin = false;
        bool isCos = false;
        bool isTan = false;
        bool isLn = false;
        bool isLog = false;
        ```
        ```C++
            //计算指数
        if(isMul)       
        {
            tempnum = pow(tempnum,downnum);
        }
        //计算阶乘
        if(isFactorial)
        {
        tempnum = factorial(tempnum);
        }
        //三角函数
        if(isSin){
            tempnum = sin(tempnum);
        }
        if(isTan)
        {
            tempnum = tan(tempnum);
        }
        if(isCos){
            tempnum = cos(tempnum);
        }
        if(isLn){
            tempnum = log(tempnum);
        }
        if(isLog){
            tempnum = log10(tempnum);
        }
        //结果入栈
        if(tempnum != 0){
            (*num).push(tempnum);
        }
        ```
       根据不同的进制计算操作数，都转化成十进制，存储在tempNum中：
       ```C++
       else{                                        //根据不同进制计算
            if(type == 1){
                tempnum += ((*numS).pop() - '0') * pow(10,k);
                k++;
            }
            else if(type == 2)
            {
                tempnum += ((*numS).pop() - '0') * pow(2,k);
                k++;
            }
            else if(type == 3)
            {
                if((*numS).topValue() >='0' && (*numS).topValue() <='9'){
                tempnum += ((*numS).pop() - '0') * pow(16,k);
                }
                else
                {
                    tempnum += ((*numS).pop() - 'a' + 10) * pow(16,k);
                }
                k++;
            }
        }
       ```
       如果有小数点的话，则按权加到tempNum中：
       ```C++
       if((*numS).topValue() == '.')
        {
            tempnum = tempnum / pow(10,k);      //遇到小数点则将原数除以位数
            k = 0;
            (*numS).pop();
        }
       ```
       扫描是否有单目运算符，并将相应的bool值赋为真：
       ```C++
       else if((*numS).topValue() == '^'){      //指数
            downnum = tempnum;                  
            tempnum = 0;
            k = 0;
            (*numS).pop();
            isMul = true;
        }
        else if((*numS).topValue() == '!'){     //阶乘
            isFactorial = true;
            (*numS).pop();
        }
        else if((*numS).topValue() == 'n'){     
            (*numS).pop();
            if((*numS).topValue() == 'i')
            {
                (*numS).pop();
                if((*numS).topValue() == 's'){      //判断是否为求sin
                    (*numS).pop();
                    isSin = true;
                }
            }
            else if((*numS).topValue() == 'a')
            {
                (*numS).pop();
                if((*numS).topValue() == 't'){      //判断是否为求tan
                    (*numS).pop();
                    isTan = true;
                }
            }
            else if((*numS).topValue() == 'l'){     //判断是否为求ln
                    (*numS).pop();
                    isLn = true;
            }
        }
        else if((*numS).topValue() == 's'){
            (*numS).pop();
            if((*numS).topValue() == 'o')
            {
                (*numS).pop();
                if((*numS).topValue() == 'c'){      //判断是否为求cos
                    (*numS).pop();
                    isCos = true;
                }
            }
        }
        else if((*numS).topValue() == 'g'){
            (*numS).pop();
                if((*numS).topValue() == 'l'){      //判断是否为求lg
                    (*numS).pop();
                    isLog = true;
                }
        }
       ```
        ####factorial模块结构：
        函数声明：
        ```C++
        int factorial(int num);
        ```
        factorial传入一个整数，然后返回它的阶乘：
        ```C++
        int factorial(int num){
        int i;
        int temp = 1;
        for(i = 1; i <= num;i++)
        {
            temp = temp * i;
            }
        return temp;
        }
        ```
        ####binaryToDecimal,hexToDecimal模块结构：
        函数声明：
        ```C++
        //二进制转十进制
        int binaryToDecimal(char *array);
        //16进制转十进制
        int hexToDecimal(char *array)
        ```
        他们都传入一个char型数组，依次压入一个栈中，然后弹出按权加到一个tempNum上，最后得到结果返回：
        ```C++
        while(array[i] != '\0'){
            stack.push(array[i]);
            i++;
        }
        ```
        binaryToDecimal:
        ```C++
        while(stack.length() != 0)
        {
            tempnum += (stack.pop() - '0') * pow(2,k);
            k++;    
        }
        ```
        hexToDecimal:
        ```C++
        while(stack.length() != 0)
        {
        if(stack.topValue() >='0' && stack.topValue() <='9'){
        tempnum += (stack.pop() - '0') * pow(16,k);
        }
        else{
            tempnum += (stack.pop() - 'a' + 10) * pow(16,k);
        }
        k++;    
        }
        ```
        ####GUI模块：
        按钮：按下一个按钮，则将按钮上的文本添加到一个Cstring上，然后格式化输出到GUI界面，例如一个“cos"按钮：
        ```C++
        void CCalculatorDlg::OnB29() 
        {
            CString str;
            GetDlgItem(EDIT)->GetWindowText(str);
            str += "cos";
            GetDlgItem(EDIT)->SetWindowText(str);   
        }
        ```
        用户选择进制单选框，将文本框清零：
        ```C++
        CString space = "";
        GetDlgItem(EDIT)->SetWindowText(space);
        ```
        将输入转化为十进制在转化为数组后输出到屏幕上,例如二进制：
        ```C++
        //处理二进制
        if(type == 2)
        {
            char *array = new char[100];
            array = (char *) str.GetBuffer(0);
            int i ;
            i = binaryToDecimal(array);
            char out[100] = {0};
            itoa(i, out,16);
            GetDlgItem(OUTPUT)->SetWindowText(out);
        }
        ```
        进制转化单选框响应，使不需要的按钮不可用，然后如上面所讲进行转换，例如二进制：
        ```C++
        GetDlgItem(B2)->EnableWindow(FALSE);
        GetDlgItem(B3)->EnableWindow(FALSE);
        GetDlgItem(B4)->EnableWindow(FALSE);
        GetDlgItem(B5)->EnableWindow(FALSE);
        GetDlgItem(B6)->EnableWindow(FALSE);
        GetDlgItem(B7)->EnableWindow(FALSE);
        GetDlgItem(B8)->EnableWindow(FALSE);
        GetDlgItem(B9)->EnableWindow(FALSE);
        GetDlgItem(B11)->EnableWindow(FALSE);
        ```

* **程序流程图:**
![](http://ww3.sinaimg.cn/large/006y8lVagw1f91fameqhgj30eo11nq43.jpg)

-----

####Chapter 3:  Testing Results 
![](http://ww2.sinaimg.cn/large/006y8lVagw1f934iv3ia6j31fw0vkn9e.jpg)
![](http://ww1.sinaimg.cn/large/006y8lVagw1f9334juxozj313a0y8n96.jpg)
![](http://ww1.sinaimg.cn/large/006y8lVagw1f9335752q0j31360i0tf7.jpg)
![](http://ww3.sinaimg.cn/large/006y8lVagw1f93358h7rpj313a0ysn9j.jpg)
![](http://ww3.sinaimg.cn/large/006y8lVagw1f9335c1yedj313a0fmaev.jpg)
![](http://ww3.sinaimg.cn/large/006y8lVagw1f9335d8eblj313c0yaqdr.jpg)
![](http://ww2.sinaimg.cn/large/006y8lVagw1f9335f9lbrj313a0i2n31.jpg)
![](http://ww1.sinaimg.cn/large/006y8lVagw1f9335gmsrdj313a0f6wi5.jpg)
----

####Chapter 4:  Analysis and Comments 

* **算法分析**

    ######时间复杂度分析
    * 在void CCalculatorDlg::OnCALCU()中从左往右扫描中缀表达式时一个循环，循环次数为中缀表达式的长度，执行时间为c1n；接下来的将剩余操作数入栈一个循环，执行时间为c2n；输出界面后缀表达式即得到express可以输出到屏幕的后缀表达式，一层循环，执行时间为c3n；
    * 在接下来的进制判断中又都调用了double calculate(char *out, int maxNum)，在calculate中从左向右扫描后缀表达式一层循环，循环次数为后缀表达式的长度，在循环中的部分分支语句中又调用了void pushNum(SList<char> *numS,SList<double> *num)，在pushNum中将字符转化为操作数，又是一层n次循环。其中最差情况为计算接触，又是一层n次循环
    * 按照最差情况计算，总的时间复杂度主要在第二点中，为&theta;(n<sup>3</sup>)
    ######空间复杂度分析
    * 本实验使用的都是一位数组或栈来存储表达式，而没有用到其他的复杂的数据结构例如二维数组，所以算法的空间复杂度只有&theta;(n)

* **算法特色**
    * 将中缀表达式转化为后缀表达式时不直接转化为后缀表达式，不将左括号丢弃，而是压入表达式中保存下来--以处理单目负，在扫描`后缀表达式`进行计算时，遇到一个左括号，如果后面跟着一个负号，则表明这个负号是一个单目负，然后将后面的操作数取负后压入栈中进行其他操作。
    * 对于其他的单目运算符如sin,cos,tan,ln,lg等，从左往右扫描后缀表达式进行匹配，如果匹配完成则将相应的bool值为真,匹配完在最后判断，如果为真的话就对操作数进行操作然后压入栈中。
    * 用户按下一个键，然后加入到一个字符串中，最后得到的字符串就是完整的用户输入的中缀表达式
    * 可以用键盘和鼠标输入，支持退格键

* **不足**
    * 没有错误检测
    * 输出的小数位数是固定的
    * 没有迭代运算，例如5*2按一次等号等于10，再按一次等于20····
    * 不支持大数乘法，也就是计算范围只能在double的精度范围之内，而不能超过这个数
    * 当计算有很多位时，不能自动用科学计数法代替，只能由用户一位一位数
    * 算法复杂度很高


-----
**Declaration**
**We hereby declare that all the work done in this project titled "project1" is of our independent effort as a group.**    
**Duty Assignments:**   
**Programmer: 方涛**  
**Tester: 朱鸿锦**     
**Report Writer: 黄智忠** 






















