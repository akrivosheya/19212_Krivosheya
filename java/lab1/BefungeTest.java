import org.junit.jupiter.api.BeforeEach;

import java.io.InputStream;

import static org.junit.jupiter.api.Assertions.*;

class BefungeTest {

    @BeforeEach
    public void initBefunge(){
        bef = new Befunge();
    }

    @org.junit.jupiter.api.Test
    void FactoryBuf() {
        InputStream in = Befunge.class.getClassLoader().getResourceAsStream("properties.txt");
        Factory.getInstance().configurate(in);
        Factory.getInstance().getCommand(String.valueOf('@'));
        Factory.getInstance().getCommand(String.valueOf('p'));
        Factory.getInstance().getCommand(String.valueOf('p'));
        Factory.getInstance().getCommand(String.valueOf('\''));
        Factory.getInstance().getCommand(String.valueOf('@'));
        Factory.getInstance().getCommand(String.valueOf('\''));
        assertEquals(3, Factory.getInstance().getSizeForTest());
    }

    @org.junit.jupiter.api.Test
    void isFinished() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\isFinished.txt"};
        bef.interpret(argv, con);
        assertEquals(0, bef.sizeForTest());
        assertTrue(bef.jobIsFinishedForTest());
        assertEquals("", con.getString());
    }

    @org.junit.jupiter.api.Test
    void tooBig1() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\tooBig1.txt"};
        bef.interpret(argv, con);
        assertEquals("java.lang.RuntimeException: File has more then 25 columns", con.getString());
    }

    @org.junit.jupiter.api.Test
    void tooBig2() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\tooBig2.txt"};
        bef.interpret(argv, con);
        assertEquals("java.lang.RuntimeException: File has more then 80 rows", con.getString());
    }

    @org.junit.jupiter.api.Test
    void noArguments() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {};
        bef.interpret(argv, con);
        assertTrue(con.getString().equals("Needs argument"));
    }

    @org.junit.jupiter.api.Test
    void noSuchFile() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"nothing"};
        bef.interpret(argv, con);
        assertTrue(con.getString().equals("Can't find file nothing"));
    }

    @org.junit.jupiter.api.Test
    void noSuchCommand() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\noSuchCommand"};
        bef.interpret(argv, con);
        assertTrue(con.getString().equals("Can't use command y"));
    }

    @org.junit.jupiter.api.Test
    void putter() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\putter.txt"};
        bef.interpret(argv, con);
        assertEquals(3, bef.sizeForTest());
        assertEquals(3, bef.getForTest());
        bef.popForTest();
        assertEquals(2, bef.getForTest());
        bef.popForTest();
        assertEquals(1, bef.getForTest());
        bef.popForTest();
        assertEquals(0, bef.sizeForTest());
        assertEquals("", con.getString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void AdditionOk() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\AdditionOk.txt"};
        bef.interpret(argv, con);
        assertEquals(3, bef.sizeForTest());
        assertEquals(11, bef.getForTest());
        assertEquals("", con.getString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void AdditionError() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\AdditionError.txt"};
        bef.interpret(argv, con);
        assertEquals("java.lang.RuntimeException: Addition needs 2 operands", con.getString());
    }

    @org.junit.jupiter.api.Test
    void SubtractionOk() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\SubtractionOk.txt"};
        bef.interpret(argv, con);
        assertEquals(3, bef.sizeForTest());
        assertEquals(1, bef.getForTest());
        assertEquals("", con.getString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void SubtractionError() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\SubtractionError.txt"};
        bef.interpret(argv, con);
        assertEquals("java.lang.RuntimeException: Subtraction needs 2 operands", con.getString());
    }

    @org.junit.jupiter.api.Test
    void MultiplicationOk() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\MultiplicationOk.txt"};
        bef.interpret(argv, con);
        assertEquals(3, bef.sizeForTest());
        assertEquals(63, bef.getForTest());
        assertEquals("", con.getString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void MultiplicationError() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\MultiplicationError.txt"};
        bef.interpret(argv, con);
        assertEquals("java.lang.RuntimeException: Multiplication needs 2 operands", con.getString());
    }

    @org.junit.jupiter.api.Test
    void DivisionOk() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\DivisionOk.txt"};
        bef.interpret(argv, con);
        assertEquals(3, bef.sizeForTest());
        assertEquals(2, bef.getForTest());
        assertEquals("", con.getString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void DivisionError() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\DivisionError.txt"};
        bef.interpret(argv, con);
        assertEquals("java.lang.RuntimeException: Division needs 2 operands", con.getString());
    }

    @org.junit.jupiter.api.Test
    void DivisionByZero() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\DivisionbyZero.txt"};
        bef.interpret(argv, con);
        assertEquals("java.lang.RuntimeException: Division by zero", con.getString());
    }

    @org.junit.jupiter.api.Test
    void ModuloOk() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\ModuloOk.txt"};
        bef.interpret(argv, con);
        assertEquals(3, bef.sizeForTest());
        assertEquals(1, bef.getForTest());
        assertEquals("", con.getString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void ModuloError() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\ModuloError.txt"};
        bef.interpret(argv, con);
        assertEquals("java.lang.RuntimeException: Modulo needs 2 operands", con.getString());
    }

    @org.junit.jupiter.api.Test
    void ModuloByZero() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\moduloByZero.txt"};
        bef.interpret(argv, con);
        assertEquals("java.lang.RuntimeException: % by zero", con.getString());
    }

    @org.junit.jupiter.api.Test
    void NegationOk() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\NegationOk.txt"};
        bef.interpret(argv, con);
        assertEquals(3, bef.sizeForTest());
        assertEquals(1, bef.getForTest());
        bef.popForTest();
        assertEquals(0, bef.getForTest());
        assertEquals("", con.getString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void NegationError() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\NegationError.txt"};
        bef.interpret(argv, con);
        assertEquals("java.lang.RuntimeException: Stack is empty", con.getString());
    }

    @org.junit.jupiter.api.Test
    void ComparerOk() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\ComparerOk.txt"};
        bef.interpret(argv, con);
        assertEquals(4, bef.sizeForTest());
        assertEquals(0, bef.getForTest());
        bef.popForTest();
        assertEquals(1, bef.getForTest());
        assertEquals("", con.getString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void ComparerError() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\ComparerError.txt"};
        bef.interpret(argv, con);
        assertEquals("java.lang.RuntimeException: Comparer needs 2 operands", con.getString());
    }

    @org.junit.jupiter.api.Test
    void Navigator() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\Navigator.txt"};
        bef.interpret(argv, con);
        assertEquals(4, bef.sizeForTest());
        assertEquals(4, bef.getForTest());
        bef.popForTest();
        assertEquals(3, bef.getForTest());
        bef.popForTest();
        assertEquals(2, bef.getForTest());
        bef.popForTest();
        assertEquals(1, bef.getForTest());
        assertEquals("", con.getString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void If() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\If.txt"};
        bef.interpret(argv, con);
        assertEquals(5, bef.sizeForTest());
        assertEquals(1, bef.getForTest());
        bef.popForTest();
        assertEquals(1, bef.getForTest());
        bef.popForTest();
        assertEquals(0, bef.getForTest());
        bef.popForTest();
        assertEquals(0, bef.getForTest());
        bef.popForTest();
        assertEquals(1, bef.getForTest());
        assertEquals("", con.getString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void VerticalIfError() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\VerticalIfError.txt"};
        bef.interpret(argv, con);
        assertEquals("java.lang.RuntimeException: Stack is empty", con.getString());
    }

    @org.junit.jupiter.api.Test
    void GorizontalIfError() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\GorizontalIfError.txt"};
        bef.interpret(argv, con);
        assertEquals("java.lang.RuntimeException: Stack is empty", con.getString());
    }

    @org.junit.jupiter.api.Test
    void StringMode() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\StringMode.txt"};
        bef.interpret(argv, con);
        assertEquals("test string mode", con.getString());
    }

    @org.junit.jupiter.api.Test
    void DuplicatorOk() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\DuplicatorOk.txt"};
        bef.interpret(argv, con);
        assertEquals(2, bef.sizeForTest());
        assertEquals(5, bef.getForTest());
        bef.popForTest();
        assertEquals(5, bef.getForTest());
        assertEquals("", con.getString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void DuplicatorError() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\DuplicatorError.txt"};
        bef.interpret(argv, con);
        assertEquals("java.lang.RuntimeException: Stack is empty", con.getString());
    }

    @org.junit.jupiter.api.Test
    void Randomizer() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\Randomizer.txt"};
        bef.interpret(argv, con);
        assertEquals("", con.getString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void SwapperOk() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\SwapperOk.txt"};
        bef.interpret(argv, con);
        assertEquals(2, bef.sizeForTest());
        assertEquals(1, bef.getForTest());
        bef.popForTest();
        assertEquals(2, bef.getForTest());
        assertEquals("", con.getString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void SwapperError() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\SwapperError.txt"};
        bef.interpret(argv, con);
        assertEquals("java.lang.RuntimeException: Swapper needs 2 operands", con.getString());
    }

    @org.junit.jupiter.api.Test
    void Popper() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\Popper.txt"};
        bef.interpret(argv, con);
        assertEquals(0, bef.sizeForTest());
        assertEquals("", con.getString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void OutputterInt() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\OutputterInt.txt"};
        bef.interpret(argv, con);
        assertEquals(1, bef.sizeForTest());
        assertEquals("4", con.getString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void OutputterChar() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\OutputterChar.txt"};
        bef.interpret(argv, con);
        assertEquals(5, bef.sizeForTest());
        assertEquals("A", con.getString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void Skipper() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\Skipper.txt"};
        bef.interpret(argv, con);
        assertEquals(2, bef.sizeForTest());
        assertEquals(2, bef.getForTest());
        bef.popForTest();
        assertEquals(1, bef.getForTest());
        assertEquals("", con.getString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void GetterError() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\GetterError.txt"};
        bef.interpret(argv, con);
        assertEquals("java.lang.RuntimeException: Getter needs 2 operands", con.getString());
    }

    @org.junit.jupiter.api.Test
    void GetterOk() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\GetterOk.txt"};
        bef.interpret(argv, con);
        assertEquals(3, bef.sizeForTest());
        assertEquals(65, bef.getForTest());
        bef.popForTest();
        assertEquals(0, bef.getForTest());
        bef.popForTest();
        assertEquals(0, bef.getForTest());
        assertTrue(bef.jobIsFinishedForTest());
        assertEquals("", con.getString());
    }

    @org.junit.jupiter.api.Test
    void ModificatorError() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\ModificatorError.txt"};
        bef.interpret(argv, con);
        assertEquals("java.lang.RuntimeException: Modificator needs 3 operands", con.getString());
    }

    @org.junit.jupiter.api.Test
    void ModificatorOk() {
        String[] buf = {""};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\ModificatorOk.txt"};
        bef.interpret(argv, con);
        assertEquals(5, bef.sizeForTest());
        assertEquals('@', (char)bef.getForTest());
        bef.popForTest();
        assertEquals(8, bef.getForTest());
        bef.popForTest();
        assertEquals(1, bef.getForTest());
        bef.popForTest();
        assertEquals(0, bef.getForTest());
        bef.popForTest();
        assertEquals(0, bef.getForTest());
        assertTrue(bef.jobIsFinishedForTest());
        assertEquals("", con.getString());
    }

    @org.junit.jupiter.api.Test
    void ReaderInt() {
        String[] buf = {"9"};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\ReaderInt.txt"};
        bef.interpret(argv, con);
        assertEquals(1, bef.sizeForTest());
        assertEquals(9, bef.getForTest());
        assertTrue(bef.jobIsFinishedForTest());
        assertEquals("", con.getString());
    }

    @org.junit.jupiter.api.Test
    void ReaderChar() {
        String[] buf = {"A"};
        ContextIOForTest con = new ContextIOForTest((buf));
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\ReaderChar.txt"};
        bef.interpret(argv, con);
        assertEquals(1, bef.sizeForTest());
        assertEquals('A', (char)bef.getForTest());
        assertTrue(bef.jobIsFinishedForTest());
        assertEquals("", con.getString());
    }

    private Befunge bef;
}
