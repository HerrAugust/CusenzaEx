/**
 */
package webApplication.data;

import webApplication.Named;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Column</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link webApplication.data.Column#getType <em>Type</em>}</li>
 *   <li>{@link webApplication.data.Column#getLenght <em>Lenght</em>}</li>
 *   <li>{@link webApplication.data.Column#isPK <em>PK</em>}</li>
 * </ul>
 *
 * @see webApplication.data.DataPackage#getColumn()
 * @model
 * @generated
 */
public interface Column extends Named {
	/**
	 * Returns the value of the '<em><b>Type</b></em>' attribute.
	 * The literals are from the enumeration {@link webApplication.data.ColumnType}.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Type</em>' attribute isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Type</em>' attribute.
	 * @see webApplication.data.ColumnType
	 * @see #setType(ColumnType)
	 * @see webApplication.data.DataPackage#getColumn_Type()
	 * @model required="true"
	 * @generated
	 */
	ColumnType getType();

	/**
	 * Sets the value of the '{@link webApplication.data.Column#getType <em>Type</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Type</em>' attribute.
	 * @see webApplication.data.ColumnType
	 * @see #getType()
	 * @generated
	 */
	void setType(ColumnType value);

	/**
	 * Returns the value of the '<em><b>Lenght</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Lenght</em>' attribute isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Lenght</em>' attribute.
	 * @see #setLenght(int)
	 * @see webApplication.data.DataPackage#getColumn_Lenght()
	 * @model
	 * @generated
	 */
	int getLenght();

	/**
	 * Sets the value of the '{@link webApplication.data.Column#getLenght <em>Lenght</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Lenght</em>' attribute.
	 * @see #getLenght()
	 * @generated
	 */
	void setLenght(int value);

	/**
	 * Returns the value of the '<em><b>PK</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>PK</em>' attribute isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>PK</em>' attribute.
	 * @see #setPK(boolean)
	 * @see webApplication.data.DataPackage#getColumn_PK()
	 * @model
	 * @generated
	 */
	boolean isPK();

	/**
	 * Sets the value of the '{@link webApplication.data.Column#isPK <em>PK</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>PK</em>' attribute.
	 * @see #isPK()
	 * @generated
	 */
	void setPK(boolean value);

} // Column
