/**
 */
package webApplication.content;


/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Multiple Content</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link webApplication.content.MultipleContent#isPaginated <em>Paginated</em>}</li>
 *   <li>{@link webApplication.content.MultipleContent#getSize <em>Size</em>}</li>
 * </ul>
 *
 * @see webApplication.content.ContentPackage#getMultipleContent()
 * @model
 * @generated
 */
public interface MultipleContent extends Content {
	/**
	 * Returns the value of the '<em><b>Paginated</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Paginated</em>' attribute isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Paginated</em>' attribute.
	 * @see #setPaginated(boolean)
	 * @see webApplication.content.ContentPackage#getMultipleContent_Paginated()
	 * @model
	 * @generated
	 */
	boolean isPaginated();

	/**
	 * Sets the value of the '{@link webApplication.content.MultipleContent#isPaginated <em>Paginated</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Paginated</em>' attribute.
	 * @see #isPaginated()
	 * @generated
	 */
	void setPaginated(boolean value);

	/**
	 * Returns the value of the '<em><b>Size</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Size</em>' attribute isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Size</em>' attribute.
	 * @see #setSize(int)
	 * @see webApplication.content.ContentPackage#getMultipleContent_Size()
	 * @model
	 * @generated
	 */
	int getSize();

	/**
	 * Sets the value of the '{@link webApplication.content.MultipleContent#getSize <em>Size</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Size</em>' attribute.
	 * @see #getSize()
	 * @generated
	 */
	void setSize(int value);

} // MultipleContent
