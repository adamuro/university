import java.io.*;
import java.util.Arrays;

public class CaesarStream {
    public static class CaesarInputStream extends InputStream {
        private InputStream stream;
        private int shift;

        public CaesarInputStream (InputStream stream, int shift) {
            this.stream = stream;
            this.shift = shift;
        }

        @Override
        public int read() throws IOException {
            int byteRead = this.stream.read();
            return byteRead + shift;
        }

        @Override
        public int read(byte[] b, int off, int len) throws IOException {
            int bytesRead = this.stream.read(b, off, len);
            for(int i = 0; i < bytesRead; i++) {
                b[i] += this.shift;
            }

            return bytesRead;
        }
    }

    public static class CaesarOutputStream extends OutputStream {
        private OutputStream stream;
        private int shift;

        public CaesarOutputStream(OutputStream stream, int shift) {
            this.stream = stream;
            this.shift = shift;
        }

        @Override
        public void write(int i) throws IOException {
            int shiftedByte = i + shift;
            this.stream.write(shiftedByte);
        }

        @Override
        public void write(byte[] b, int off, int len) throws IOException {
            byte[] shiftedBytes = new byte[len];

            for(int i = 0; i < len; i++) {
                shiftedBytes[i] += b[i] + this.shift;
            }

            this.stream.write(shiftedBytes, off, len);
        }
    }

    public static void main(String[] args) {
        try {
            /* Input stream */
            InputStream normalInStream = new FileInputStream(new File("in.txt"));
            InputStream inStream = new FileInputStream(new File("in.txt"));
            CaesarInputStream caesarInStream = new CaesarInputStream(inStream, 3);

            byte[] normalBuffer = new byte[10];
            byte[] caesarBuffer = new byte[10];

            normalInStream.read(normalBuffer, 0, 10);
            caesarInStream.read(caesarBuffer, 0, 10);

            System.out.println("Oryginalne bajty:");
            System.out.println(Arrays.toString(normalBuffer));
            System.out.println("Przesunięte bajty:");
            System.out.println(Arrays.toString(caesarBuffer));

            /* Output stream */
            OutputStream outStream = new FileOutputStream(new File("out.txt"));
            CaesarOutputStream caesarOutStream = new CaesarOutputStream(outStream, 5);

            byte[] outBuffer = ("ala ma kota").getBytes();

            caesarOutStream.write(outBuffer, 0, 10);

            System.out.println("Napis \"ala ma kota\" wypisany przez CaesarOutputStream są w pliku out.txt");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
