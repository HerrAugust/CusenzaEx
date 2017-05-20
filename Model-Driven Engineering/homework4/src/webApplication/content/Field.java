/**
 */
package webApplication.content;

import webApplication.Named;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Field</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link webApplication.content.Field#getType <em>Type</em>}</li>
 * </ul>
 *
 * @see webApplication.content.ContentPackage#getField()
 * @model
 * @generated
 */
public interface Field extends Named {
	/**
	 * Returns the value of the '<em><b>Type</b></em>' attribute.
	 * The literals are from the enumeration {@link webApplication.content.FieldType}.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Type</em>' attribute isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Type</em>' attribute.
	 * @see webApplication.content.FieldType
	 * @see #setType(FieldType)
	 * @see webApplication.content.ContentPackage#getField_Type()
	 * @model
	 * @generated
	 */
	FieldType getType();

	/**
	 * Sets the value of the '{@link webApplication.content.Field#getType <em>Type</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Type</em>' attribute.
	 * @see webApplication.content.FieldType
	 * @see #getType()
	 * @generated
	 */
	void setType(FieldType value);

} // Field
