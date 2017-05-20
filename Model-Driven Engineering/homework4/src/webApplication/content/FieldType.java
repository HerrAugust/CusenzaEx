/**
 */
package webApplication.content;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import org.eclipse.emf.common.util.Enumerator;

/**
 * <!-- begin-user-doc -->
 * A representation of the literals of the enumeration '<em><b>Field Type</b></em>',
 * and utility methods for working with them.
 * <!-- end-user-doc -->
 * @see webApplication.content.ContentPackage#getFieldType()
 * @model
 * @generated
 */
public enum FieldType implements Enumerator {
	/**
	 * The '<em><b>Text Box</b></em>' literal object.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #TEXT_BOX_VALUE
	 * @generated
	 * @ordered
	 */
	TEXT_BOX(0, "TextBox", "TextBox"),

	/**
	 * The '<em><b>Check Box</b></em>' literal object.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #CHECK_BOX_VALUE
	 * @generated
	 * @ordered
	 */
	CHECK_BOX(1, "CheckBox", "CheckBox"),

	/**
	 * The '<em><b>Radio Button</b></em>' literal object.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #RADIO_BUTTON_VALUE
	 * @generated
	 * @ordered
	 */
	RADIO_BUTTON(3, "RadioButton", "RadioButton"),

	/**
	 * The '<em><b>Submit Button</b></em>' literal object.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #SUBMIT_BUTTON_VALUE
	 * @generated
	 * @ordered
	 */
	SUBMIT_BUTTON(4, "SubmitButton", "SubmitButton");

	/**
	 * The '<em><b>Text Box</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of '<em><b>Text Box</b></em>' literal object isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @see #TEXT_BOX
	 * @model name="TextBox"
	 * @generated
	 * @ordered
	 */
	public static final int TEXT_BOX_VALUE = 0;

	/**
	 * The '<em><b>Check Box</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of '<em><b>Check Box</b></em>' literal object isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @see #CHECK_BOX
	 * @model name="CheckBox"
	 * @generated
	 * @ordered
	 */
	public static final int CHECK_BOX_VALUE = 1;

	/**
	 * The '<em><b>Radio Button</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of '<em><b>Radio Button</b></em>' literal object isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @see #RADIO_BUTTON
	 * @model name="RadioButton"
	 * @generated
	 * @ordered
	 */
	public static final int RADIO_BUTTON_VALUE = 3;

	/**
	 * The '<em><b>Submit Button</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of '<em><b>Submit Button</b></em>' literal object isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @see #SUBMIT_BUTTON
	 * @model name="SubmitButton"
	 * @generated
	 * @ordered
	 */
	public static final int SUBMIT_BUTTON_VALUE = 4;

	/**
	 * An array of all the '<em><b>Field Type</b></em>' enumerators.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private static final FieldType[] VALUES_ARRAY =
		new FieldType[] {
			TEXT_BOX,
			CHECK_BOX,
			RADIO_BUTTON,
			SUBMIT_BUTTON,
		};

	/**
	 * A public read-only list of all the '<em><b>Field Type</b></em>' enumerators.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public static final List<FieldType> VALUES = Collections.unmodifiableList(Arrays.asList(VALUES_ARRAY));

	/**
	 * Returns the '<em><b>Field Type</b></em>' literal with the specified literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param literal the literal.
	 * @return the matching enumerator or <code>null</code>.
	 * @generated
	 */
	public static FieldType get(String literal) {
		for (int i = 0; i < VALUES_ARRAY.length; ++i) {
			FieldType result = VALUES_ARRAY[i];
			if (result.toString().equals(literal)) {
				return result;
			}
		}
		return null;
	}

	/**
	 * Returns the '<em><b>Field Type</b></em>' literal with the specified name.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param name the name.
	 * @return the matching enumerator or <code>null</code>.
	 * @generated
	 */
	public static FieldType getByName(String name) {
		for (int i = 0; i < VALUES_ARRAY.length; ++i) {
			FieldType result = VALUES_ARRAY[i];
			if (result.getName().equals(name)) {
				return result;
			}
		}
		return null;
	}

	/**
	 * Returns the '<em><b>Field Type</b></em>' literal with the specified integer value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the integer value.
	 * @return the matching enumerator or <code>null</code>.
	 * @generated
	 */
	public static FieldType get(int value) {
		switch (value) {
			case TEXT_BOX_VALUE: return TEXT_BOX;
			case CHECK_BOX_VALUE: return CHECK_BOX;
			case RADIO_BUTTON_VALUE: return RADIO_BUTTON;
			case SUBMIT_BUTTON_VALUE: return SUBMIT_BUTTON;
		}
		return null;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private final int value;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private final String name;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private final String literal;

	/**
	 * Only this class can construct instances.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private FieldType(int value, String name, String literal) {
		this.value = value;
		this.name = name;
		this.literal = literal;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public int getValue() {
	  return value;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public String getName() {
	  return name;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public String getLiteral() {
	  return literal;
	}

	/**
	 * Returns the literal value of the enumerator, which is its string representation.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public String toString() {
		return literal;
	}
	
} //FieldType
