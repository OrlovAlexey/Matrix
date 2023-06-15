#include <iostream>
#include "Matrix/SquareMatrix.h"


BigInteger bin_pow(BigInteger a, BigInteger degree) {
    if (degree == 0) {
        return 1;
    }
    if (degree % 2 != 0) {
        BigInteger c = bin_pow(a, degree - 1) * a;
        return c;
    }
    else {
        BigInteger b = bin_pow(a, degree / 2);
        return b * b;
    }
}

int main() {
    Matrix<3,3,double> m1;
//    cin >> m1;
//    cout << m1;

    SquareMatrix<3, double> s;
    cout << s;

/*
//    vector<vector<int>> a{{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1}};
//    const Matrix<4,5,Finite<17>> am(a);
//    vector<vector<int>> b{{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};
//    const Matrix<5,4,Finite<17>> bm(b);
//    am*bm;
    Finite<17> b1(1);
    Finite<17> b2(16);
//    cout << bin_pow_mod(2, 6, 10000) <<'\n';
    for (int i = 1; i < 17; ++i) cout << (Finiteinverse(Finite<17>(i)).num * Finite<17>(i).num) << '\n';
    cout << (b1 != b1-b2) << '\n';
    vector<vector<int>> vvi{{0, 0}, {0, 0}};
    Matrix<2, 3> m1(vvi);
    SquareMatrix<2> m2({{8, 7}, {4, 3}});
//    Matrix<2, 2, int> m3 = m1 * m2;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            cout << m2.mat[i][j] << '\t';
        }
        cout << '\n';
    }
//    m2.invert();
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            cout << m2.inverted().mat[i][j] << '\t';
        }
        cout << '\n';
    }
//    cout << Finiteinverse(a-b).num;
//    cout << gcd2(BigInteger(1802735), BigInteger(3248971));
//    clock_t start1 = clock();
//    for (int i = 1; i < 1000; ++i) {
//        for (int k = 1; k < 100; ++k) {
//            gcd(BigInteger(i+k), BigInteger(i));
//        }
//    }
//    clock_t end1 = clock();
//    double seconds1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
//    cout << seconds1 << " seconds\n";
//    clock_t start2 = clock();
//    for (int i = 1; i < 1000; ++i) {
//        for (int k = 1; k < 100; ++k) {
//            gcd2(BigInteger(i+k), BigInteger(i));
//        }
//    }
//    clock_t end2 = clock();
//    double seconds2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
//    cout << seconds2 << " seconds\n";
*/

/*

   Finite<433494437> x = 1279;
    (x == 1279);
    x *= x += x *= ++x;
    for (int i = 0; i < 1000000; ++i)
        ++x;
    auto y = Finite<433494437>(1) / x;
    if (y*x != Finite<433494437>(1))
        throw std::runtime_error("Finite Finite arithmetic failed.");

    using std::vector;
    vector<vector<int>> a = { {8,-4,-5,5,9},
                              {1,-3,-5,0,-7},
                              {7,-5,1,4,1},
                              {3,-1,3,2,5} };
    vector<vector<int>> b = { {4,0,3,2},
                              {1,-7,4,5},
                              {7,1,5,3},
                              {-5,-3,-3,-1},
                              {1,-5,2,3} };
    const Matrix<4, 5, Finite<17>> am = a;
    const Matrix<5, 4, Finite<17>> bm = b;
    if (am.rank() != 4 || bm.rank() != 3)
        throw std::runtime_error("rank() method failed.");
    vector<vector<int>> ab = { {-23, -37, -14, 3},
                               {-41, 51, -48, -49},
                               {11, 19, -4, -9},
                               {27, -21, 24, 23} };

    const auto abm = am * bm;
    if (abm != SquareMatrix<4, Finite<17>>(ab))
        throw std::runtime_error("matrix multiplication or constructors failed.");

    const auto aminusb = am - bm.transposed();
    vector<vector<int>> diff = {
            {4, -5, -12, 10, 8},
            {1, 4, -6, 3, -2},
            {4, -9, -4, 7, -1},
            {1, -6, 0, 3, 2}
    };
    if (aminusb != Matrix<4, 5, Finite<17>>(diff))
        throw std::runtime_error("Addition or subtraction failed.");

    auto newMatrix = Finite<17>(2) * aminusb * bm;
    newMatrix[2][2] = 1;

    if (newMatrix.det() != Finite<17>(14420160))
        throw std::runtime_error("Determinant is wrong.");
    if (newMatrix.trace() != Finite<17>(-345))
        throw std::runtime_error("Trace is wrong.");


    Matrix<4, 4, Finite<17>> F = newMatrix.inverted();
    Matrix<4, 4, Finite<17>> G = F * newMatrix;
    if (F * newMatrix != Matrix<4, 4, Finite<17>>())
        throw std::runtime_error("A*A^(-1) must be equal to unity matrix.");


//    Rational r;
//    cin >> r;


//    ifstream in;
//    in.open("matr.txt");
//    if(in.is_open()) cout << "da";
//    else cout << "net";
vector<vector<int>> big_vvi = {{87, 15, -69, -56, 58, -85, 52, -59, -72, 88, 60, -48, -43, -80, 6, -91, -44, -72, -47, 9},
                               {-8, 10, 26, -10, -24, 31, -96, 58, 81, -73, 95, 15, 82, -37, -10, 22, -64, -35, -52, -77},
                               {-65, 36, -53, -32, -42, 69, -42, 85,-80, -52, 25, -59, 57, 49, -71, 21, 59, 5, 39, -91},
                               {32,-29,-57,5,-22,-92,-7,85,74,30,64,-64,-71,21,1,-35,-25,-54,-73,-44},
                               {-31,38,74,13,-86,35,94,18,67,40,-60,32,-33,83,-45,-95,-41,-1,-65,-26},
                               {-97,73,-57,7,86,45,50,52,73,69,74,-90,33,33,96,-58,-1,-21,-66,45},
                               {-75,-83,-30,67,30,59,-66,-46,-54,82,-52,60,-31,1,-58,-17,53,-19,87,3},
                               {83,51,53,-30,-68,-96,-71,65,90,-55,-22,51,92,50,-61,-14,-18,80,58,41},
                               {-4,-54,-48,-51,1,-93,-28,-83,52,-84,7,69,80,81,-98,1,-93,-45,-95,-45},
                               {53,-78,16,10,44,-55,76,83,78,-80,47,45,-28,-79,12,42,-100,77,73,81},
                               {-53,92,39,-96,-46,44,-68,87,96,48,60,-55,-8,26,-84,65,-23,-44,98,6},
                               {18,48,-27,45,14,61,-38,-38,47,-70,-97,50,-17,13,72,54,-3,92,83,-41},
                               {91,-9,94,81,-61,-66,-25,84,-57,55,-55,-99,-51,-71,-56,-41,-74,-90,-84,16},
                               {-76,-51,-63,83,21,91,-92,-97,23,66,-61,69,96,8,-10,-75,25,-9,-18,44},
                               {63,-80,-21,-86,-40,-89,23,-24,-6,10,-67,49,25,18,49,26,68,-48,55,-95},
                               {-92,-62,-68,0,59,81,20,81,-86,88,-66,65,-23,70,98,-80,-61,-74,32,-89},
                               {29,83,22,55,-75,34,-92,9,69,79,89,77,81,-74,-87,-95,-95,-92,99,29},
                               {-98,47,-30,87,-71,-75,-51,-40,-22,50,52,29,-2,-69,-18,-20,-73,-91,17,-86},
                               {-89,-24,-81,79,-65,63,-58,-23,22,-25,-31,70,-44,97,-90,5,9,-84,-19,-63},
                               {-36,17,-30,51,78,-1,-85,-9,6,97,16,4,25,4,78,2,-62,-87,80,51}};
    SquareMatrix<20> bigMatrix = big_vvi;
//    for (int i = 0; i < 20; ++i)
//        for (int j = 0; j < 20; ++j)
//            in >> bigMatrix[i][j];

    vector<vector<double>> bigInvertedMatrix =
    {{-0.03980673507548272,-0.0334427702291123,-0.019021390180314526,0.019408509690651585,-0.0376001314060556,0.011510699181575806,0.000325727814426909,-0.01724267120838151,0.027594730524077293,-0.02098074718764331,1.974221259389164e-05,0.010349740376194896,0.006680459912355107,-0.015477695241824227,-0.0066161069554688395,0.01870281101225305,0.03996610199523166,-0.005718085885895894,-0.022636726026529923,-0.03891623235364354},
        {-0.019071279614811917,-0.01750188522226693,-0.014762843893213357,0.00329931612058809,-0.024338986427632825,0.013842373216248292,0.0020790547593249314,-0.0038709259009265273,0.014286068055625772,-0.013174023804801756,0.0019507728938763253,0.006953699508971619,0.005438816501806874,-0.012302233575565045,-0.0040938924459481855,0.012031342507955506,0.02047648561304339,0.000507126283710635,-0.007512751040400777,-0.027088191477180334},
        {0.027466702020206714,0.02808064682444818,0.014025148420542786,-0.013759128790225556,0.031923544820447736,-0.010018106898607854,0.004375099145044182,0.011238912460703033,-0.019472613141633833,0.012790995363375392,-0.0037163144951596725,-0.007547682920822535,-0.004802983016033314,0.0056584587832094095,0.005165339074717741,-0.016334083753486186,-0.027154898757682868,0.000252000578224294,0.013136959827133955,0.03323429702545551},
        {-0.03326940711093151,-0.02576299010396252,-0.013103589244482057,0.014142056519563753,-0.027392252347241595,0.012530677024582987,0.004152798700439746,-0.013345125790826645,0.021632324888052633,-0.01488457135948581,-0.0031487962673819024,0.00820076207391229,0.0062411003853027275,-0.013899240494372371,-0.005222431744113978,0.01215346513036174,0.030357031065317515,-0.0014897051961025869,-0.016960101753844534,-0.028262326534169564},
        {-0.006460457961765173,-0.003061358299338592,-0.007373802307938397,-0.001613174860815454,-0.010715231820299043,0.01325651983985546,0.012619565029930972,-0.0005692312838025779,0.009841822859958703,-0.005515858932734125,-0.0014191501605146353,0.005477094271078656,0.004665705278469795,-0.012027184546745385,-0.000454571184903437,0.004174220256771421,0.008616220404296085,-0.002560526164452839,-0.003930837521458452,-0.01218324834060779},
        {-0.00806425173627508,-0.0059271591410410196,-0.002183208874051748,0.004188635726135654,-0.005810420856214026,-0.0005173316063210505,-0.0026769529349547658,-0.007062991815365669,0.004338396165659664,-0.003626060943642333,0.0011492172848955675,0.002290758003072763,0.00043673681943474967,-0.00017039810598274219,-0.002413520676680991,0.004008503049394161,0.008717733926243794,-0.0032815929304709497,-0.004602944217448887,-0.006851621748540057},
        {-0.031034137884233724,-0.027345557976326478,-0.013679161733503484,0.010360175422958397,-0.027047160339168774,0.014087669701901978,0.0013038368761410248,-0.014382610936351712,0.02211035882456677,-0.01267376617767136,0.00027840796770760626,0.006863450820141114,0.005874496861050219,-0.012990105810346987,-0.0024583578350420143,0.01363795739354101,0.029955608131783076,-0.0015047480483354032,-0.016299470602787195,-0.0320109988835836},
        {-0.02770166358219391,-0.021976981022449237,-0.01668594899666147,0.009003484343075366,-0.03109583256357023,0.014421265331981339,0.002173693516442458,-0.006353298192492137,0.017349709347034566,-0.013156274103603751,0.0024894122306824682,0.005168408847828613,0.007382144230494783,-0.011817489252200917,-0.0043200714918877675,0.01745731160489028,0.025422390084387667,-0.0009886020813449604,-0.011680259400029445,-0.034083880707518874},
        {0.010793066797193742,0.01046541698254154,0.0040768347059232015,-0.003863552939731488,0.011377331862560134,0.0004312142013604767,0.002756226414100766,0.00376953362860966,-0.006326764178403853,0.006548274485964103,0.000633680510244222,0.00040664603974168453,-0.0007991474679281786,0.0037227232044688553,0.004635158535338584,-0.007402799147572177,-0.00930660236534497,-0.0002170408251651598,0.006148573257711201,0.009609821528991647},
        {-0.09392967226996811,-0.07870259591279227,-0.047909270620526835,0.04210485907941368,-0.08796118565065594,0.02955102745087736,0.002626258095506773,-0.03730104103535207,0.06306548388903732,-0.047702684089974336,0.00724474602003479,0.01957591441447268,0.01450385197808569,-0.030595333693319616,-0.01700494879992575,0.04706742734318506,0.08561918116848177,-0.003075400459052902,-0.05467944049495926,-0.09530900217342385},
        {-0.012462707998196173,-0.008100515356692916,-0.003098316557155226,0.009577115926094318,-0.007637500669769631,-0.0014527112796468853,-0.0007997526099166839,-0.006817456177457009,0.006373876231938915,-0.006210640752501842,-0.002302688125592678,-0.0010571295828403274,-0.0034809240194630026,-0.005103251115210082,-0.0046851802637908,0.0035280688082718584,0.01164353922338357,-0.0013047028713086303,-0.008551067388441467,-0.005931321873288805},
        {-0.04677966698978926,-0.03763512634203241,-0.03210983953251577,0.014813766864195652,-0.05113539227461095,0.019715171755691884,0.0028663161673292688,-0.013120751253238673,0.030815291042949854,-0.02529349902286387,0.00280504587765403,0.008477716737959037,0.007446214018238241,-0.020334608314572636,-0.008668519018828494,0.02825476780717243,0.04456064560229125,-0.0009621307222548334,-0.020392502445176895,-0.05610180541922169},
        {-0.0368229255704948,-0.029489759403892177,-0.014269476194164356,0.013111296503730744,-0.03278420513587876,0.013941159049781797,0.0001012386986240944,-0.014540848489152049,0.025883664539132937,-0.016545904751322622,0.0005673840475612487,0.007260012360162407,0.006978923320952536,-0.010765981468652838,-0.0035629774004779648,0.01613237082701017,0.03372662416932441,-0.0016054083440472902,-0.02162911874082671,-0.03460773717276243},
        {-0.009567532000240624,-0.007695420913206437,0.0002815729831657237,0.007607135720686366,-0.0017757311066153524,-0.002456421292138333,-0.0013604267301057338,-0.0041818722196161505,0.006145416897052916,-0.005161512125328631,-0.0023726678602851285,9.011611831343667e-05,-0.0021862895929485016,-0.003815921347034042,-0.0031980611704901184,0.001988331350105235,0.006768883677928005,-0.0030813697234234124,-0.005697993749460294,0.0012180453841779063},
        {0.026543124829591685,0.023118216294356574,0.01386462917629397,-0.009246050838154388,0.027473147610621272,-0.013871703876219511,-0.007354176315419684,0.009954787563105342,-0.022191836746117882,0.013435417470052304,-0.002395638119568375,-0.007471559821476194,-0.007204410044768728,0.012978686328651965,0.004714411313875504,-0.012814929288393338,-0.026931695542459434,0.0018527763940369177,0.014430838198202603,0.03275886638093032},
        {-0.09805988667949435,-0.08069951101303419,-0.0501854173983066,0.03893181200258045,-0.09435271364910168,0.03211876092370433,-2.0422449345599346e-05,-0.038974018625937315,0.06566311989019871,-0.04755082419467915,0.007795239538556619,0.02047763580422268,0.016624456705346475,-0.03378431927165563,-0.016460879743572014,0.04761789795117654,0.08721352141903256,-0.0032580251508296056,-0.05129701113321224,-0.09868259815128738},
        {0.007650993156783143,0.008045361678307291,0.0005448583512796133,-0.006297293294139022,0.0035773174303571176,0.004237675517135603,0.005387825000594869,0.006304882200129095,-0.007005188138578865,0.0016050332371712675,-0.0020418800632847588,-0.0024569138138590377,-0.0003048922790576203,-0.0015548753536986405,0.004452550521762051,-0.0046642376697890765,-0.0061558379348132025,-0.00048623623096902654,0.00798352266989869,0.0027038398539667827},
        {-0.038240931162820194,-0.03229210642031696,-0.016851737501702012,0.020982703923907945,-0.03344998579743943,0.0073014862196178,8.294446483909523e-05,-0.01465884761621893,0.02509408482442312,-0.01873775871879259,0.0024402843985121803,0.008986761739424563,0.002939571387550536,-0.009470992032396087,-0.010767536879780139,0.018965054372473897,0.032701044680873426,-8.489549226617974e-05,-0.026563835492105184,-0.03811326173898657},
        {0.043846702827215624,0.03521788273327868,0.027262436167385256,-0.017157162310182567,0.04589067561056726,-0.01656524164865648,0.0005754440465951224,0.015252866772151062,-0.029593896273478436,0.024082174574609518,-0.0035761397942022364,-0.008164444863116436,-0.008517210975801399,0.014575543897145738,0.00947068831196929,-0.02448205221308016,-0.039032950157687374,0.001196835699305794,0.021872214425582428,0.0507363335633662},
        {0.02309314389227609,0.015888199430313436,0.009358491868887103,-0.011381641842516813,0.019011514174624742,-0.009612610310299837,-0.0070376788835833076,0.010876407920347633,-0.018136688196191048,0.012843718570399938,0.0006277289932144235,-0.009038524126698588,-0.004059825360283541,0.012149280133321243,0.002312161626316476,-0.010284390581453577,-0.022201696804222085,0.000671015999370556,0.016536297805306157,0.023836656980169464}};
//    for (int i = 0; i < 20; ++i)
//        for (int j = 0; j < 20; ++j)
//            in >> bigInvertedMatrix[i][j];
    clock_t end1 = clock();
    double seconds1 = (double)(end1 - start) / CLOCKS_PER_SEC;
    cout << seconds1 << " seconds ввод матриц и начало\n";

    clock_t start1 = clock();

    auto anotherMatrix = bigMatrix;
//    //bigMatrix.inverted();
    bigMatrix.invert();
    cout << bigMatrix.det() << '\n';
    clock_t end2 = clock();
    double seconds2 = (double)(end2 - start1) / CLOCKS_PER_SEC;
    cout << seconds2 << " seconds инвертирование\n";
    clock_t start2 = clock();

    std::cout << "Big matrix inverted!\n";
    for (int i = 0; i < 20; ++i) {
        auto row = bigMatrix.getRow(i);
        auto anotherRow = bigInvertedMatrix[i];
        for (int j = 0; j < 20; ++j) {
            if (!((static_cast<double>(row[j]) - anotherRow[j]) < 1e-6 && (static_cast<double>(row[j]) - anotherRow[j]) > -1e-6)) {

                throw std::runtime_error("Inverted matrix is incorrect!");
            }
        }
    }
    clock_t end3 = clock();
    double seconds3 = (double)(end3 - start2) / CLOCKS_PER_SEC;
    cout << seconds3 << " seconds непонятное штука\n";
    clock_t start3 = clock();

    std::cout << "Inverted matrix is correct!\n";
    bigMatrix *= anotherMatrix;
//    for (int i = 0; i < 20; ++i) {
//        for (int j = 0; j < 20; ++j) {
//            cout << bigMatrix.mat[i][j] << '\t';
//        }
//        cout << '\n';
//    }
    Rational(BigInteger("30441155735900550591765790657738378873752658"));

    std::cout << "Matrix multiplied by its inverted matrix!\n";
    SquareMatrix<20> unity = SquareMatrix<20>();
    for (int j = 0; j < 20; ++j) {
        auto column = bigMatrix.getColumn(j);
        auto unityColumn = unity.getColumn(j);
        for (int i = 0; i < 20; ++i) {
            if (column[i] != unityColumn[i]) {
                throw std::runtime_error("Product of A and A^(-1) must be equal to unity matrix.");
            }
        }
    }

    clock_t end4 = clock();
    double seconds4 = (double)(end4 - start3) / CLOCKS_PER_SEC;
    cout << seconds4 << " seconds произведение\n";
    clock_t start4 = clock();

    std::cout << "Result of A*A^(-1) is correct!\n";

    auto det = anotherMatrix.det();
    std::cout << "Determinant is computed!\n";

    clock_t end5 = clock();
    double seconds5 = (double)(end5 - start4) / CLOCKS_PER_SEC;
    cout << seconds5 << " seconds детерминант\n";
    clock_t start5 = clock();

    //det /= 20;
    cout << det << '\n';
    for (int i = 0; i < 20; ++i)
        anotherMatrix[0][i] /= det;
    // now anotherMatrix is orthogonal matrix
    if (anotherMatrix.det() != 1)
        throw std::runtime_error("Dividing a row by det must make the determinant equal to 1.");

    clock_t end6 = clock();
    double seconds6 = (double)(end6 - start5) / CLOCKS_PER_SEC;
    cout << seconds6 << " seconds еще один детерминант\n";
    clock_t start6 = clock();

    auto transposedMatrix = anotherMatrix.transposed();
    if ((anotherMatrix *= transposedMatrix).det() != 1)
        throw std::runtime_error("Product of two matrices with det=1 must give the matrix with same determinant.");

    clock_t end7 = clock();
    double seconds7 = (double)(end7 - start6) / CLOCKS_PER_SEC;
    cout << seconds7 << " seconds конечная\n";

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << seconds << " seconds всего\n";

    */
    return 0;
}