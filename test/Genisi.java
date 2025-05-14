public class Genisi {
    public native String getVersion();    public native void InitMemory(); 
    public native void CloseMemory();
    static {
        System.loadLibrary("genisi");
    }

    public static void main(String[] args) {
        String versao = new Genisi().getVersion();
        if (versao != null) {
            System.out.println("Versão da lib: " + versao);
        } else {
            System.out.println("Erro ao carregar versão.");
        }
        new Genisi().InitMemory();
        new Genisi().CloseMemory();
    }
}