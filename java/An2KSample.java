import eu.id3.an2k.*;

public class An2KSample {

    public static void main(String[] args) {
        System.out.println("-------------------------------");
        System.out.println("id3 An2KSample");
        System.out.println("-------------------------------");

        // Before calling any function of the SDK you must first check a valid license file.
        // To get such a file please use the provided activation tool.
        An2KLibrary.checkLicense("your_license_path_here");

        // The sample transaction file comes from NIST website and is presented as reference transaction
        // with all record types 
        // source: https://www.nist.gov/itl/iad/image-group/ansinist-itl-standard-references
        String transaction_filepath = "../data/pass-all-supported-types.an2";

        System.out.println("Loading transaction: " + transaction_filepath);
        // Transaction files can be either loaded as file or buffers
        eu.id3.an2k.Transaction tr = Transaction.fromFile(transaction_filepath);

        // Print a convenient summary of the transaction content
        System.out.println(tr.getSummary());

        // Retrieve the transaction information record
        System.out.println("Access record n.0:");
        eu.id3.an2k.Record tr_information_rec = tr.get(0);
        System.out.println("Record type: " + tr_information_rec.getRecordType());
        System.out.println("IDC: " + tr_information_rec.getIdc());
        System.out.println("Field count: " + tr_information_rec.getCount());

        // Fields can be accessed by three ways:
        // - by index (from 0 to field count -1)
        // - by field number, for example field 1.005 number is 5
        // - by field mnemonic, for example field 1.005 mnemonic is DAT

        // In the sample transaction we have the field 1.005 DAT at index 4
        eu.id3.an2k.Field f_dat_by_index = tr_information_rec.get(4);
        System.out.println("Field access by index: " + f_dat_by_index.getDescription());
        eu.id3.an2k.Field f_dat_by_number = tr_information_rec.getFieldByFieldNumber(5);
        System.out.println("Field access by field number: " + f_dat_by_number.getDescription());
        eu.id3.an2k.Field f_dat_by_mnemonic = tr_information_rec.getFieldByMnemonic("DAT");
        System.out.println("Field access by field mnemonic: " + f_dat_by_mnemonic.getDescription());

        // Field data can be retrieved either as raw buffer of string, please remember that subfields are not parsed
        // To access subfield data the user must parse the data according to the field encoding type given by the norm
        byte[] data_buffer = f_dat_by_mnemonic.getData();
        String string_data = f_dat_by_mnemonic.getStringData();
        System.out.println("Field string data: " + string_data);

        // Fields can of course be modified:
        data_buffer[0] = '2';
        data_buffer[1] = '0';
        data_buffer[2] = '2';
        data_buffer[3] = '2';
        f_dat_by_mnemonic.setData(data_buffer);
        System.out.println("Field updated string data: " + f_dat_by_mnemonic.getStringData());

        // Updated transaction can then be re-exported 
        tr.toFile("saved-transaction.an2");
        System.out.println("Saving transaction to ./saved-transaction.an2");
        
        // Re-opening to check 
        eu.id3.an2k.Transaction tr2 = Transaction.fromFile("saved-transaction.an2");
        // Field quick access example
        System.out.println("Re-opened transaction date: " + tr2.get(0).getFieldByMnemonic("DAT").getStringData());

        System.out.println("Sample terminated successfully.");
    }
}

