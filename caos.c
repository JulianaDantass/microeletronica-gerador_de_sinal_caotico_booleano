#include <genlib.h>
#include <stdio.h>

int main(void){
    int i;

    int n1 = 134; 
    int n2 = 237; 
    int n3 = 47;  

    GENLIB_DEF_LOFIG("GERADOR_CAOS");

    // ===============================
    // CONECTORES
    // ===============================
    GENLIB_LOCON("P", IN, "P");
    GENLIB_LOCON("S", OUT, "S");
    GENLIB_LOCON("vdd", IN, "vdd");
    GENLIB_LOCON("vss", IN, "vss");

    // ===============================
    // CONTROLE (P + NAND)
    // ===============================
    // p_inv = NOT(P)
    GENLIB_LOINS("inv_x1", "inv_p", "P", "p_inv", "vdd", "vss", NULL);

    // fback = NAND(fback_raw, p_inv)
    GENLIB_LOINS("na2_x1", "nand_control", "fback_raw", "p_inv", "fback", "vdd", "vss", NULL);

    // ===============================
    // LINHA DE ATRASO T1
    // ===============================
    GENLIB_LOINS("inv_x1", "inv_t1_0", "fback", "node_t1_1", "vdd", "vss", NULL);

    for (i = 1; i < n1 - 1; i++) {
        GENLIB_LOINS("inv_x1", GENLIB_NAME("inv_t1_%d", i),
            GENLIB_NAME("node_t1_%d", i),
            GENLIB_NAME("node_t1_%d", i+1),
            "vdd", "vss", NULL);
    }

    GENLIB_LOINS("inv_x1", "inv_t1_final",
        GENLIB_NAME("node_t1_%d", n1-1),
        "i_n1", "vdd", "vss", NULL);

    // ===============================
    // LINHA DE ATRASO T2
    // ===============================
    GENLIB_LOINS("inv_x1", "inv_t2_0", "fback", "node_t2_1", "vdd", "vss", NULL);

    for (i = 1; i < n2 - 1; i++) {
        GENLIB_LOINS("inv_x1", GENLIB_NAME("inv_t2_%d", i),
            GENLIB_NAME("node_t2_%d", i),
            GENLIB_NAME("node_t2_%d", i+1),
            "vdd", "vss", NULL);
    }

    GENLIB_LOINS("inv_x1", "inv_t2_final",
        GENLIB_NAME("node_t2_%d", n2-1),
        "i_n2", "vdd", "vss", NULL);

    // ===============================
    // LINHA DE ATRASO T3
    // ===============================
    GENLIB_LOINS("inv_x1", "inv_t3_0", "fback", "node_t3_1", "vdd", "vss", NULL);

    for (i = 1; i < n3 - 1; i++) {
        GENLIB_LOINS("inv_x1", GENLIB_NAME("inv_t3_%d", i),
            GENLIB_NAME("node_t3_%d", i),
            GENLIB_NAME("node_t3_%d", i+1),
            "vdd", "vss", NULL);
    }

    GENLIB_LOINS("inv_x1", "inv_t3_final",
        GENLIB_NAME("node_t3_%d", n3-1),
        "i_n3", "vdd", "vss", NULL);

    // ===============================
    // XORs (lógica caótica)
    // ===============================
    // XOR1: T3 ⊕ T2
    GENLIB_LOINS("xr2_x1", "xor1", "i_n3", "i_n2", "A", "vdd", "vss", NULL);

    // XOR2: A ⊕ T1 → fback_raw
    GENLIB_LOINS("xr2_x1", "xor2", "A", "i_n1", "fback_raw", "vdd", "vss", NULL);

    // ===============================
    // SAÍDA
    // ===============================
    GENLIB_LOINS("inv_x1", "buf_s", "fback", "S", "vdd", "vss", NULL);

    GENLIB_SAVE_LOFIG();
    return 0;
}