/**
 */
package webApplication.content;

import webApplication.Named;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Link</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link webApplication.content.Link#getFrom <em>From</em>}</li>
 *   <li>{@link webApplication.content.Link#getTo <em>To</em>}</li>
 * </ul>
 *
 * @see webApplication.content.ContentPackage#getLink()
 * @model
 * @generated
 */
public interface Link extends Named {
	/**
	 * Returns the value of the '<em><b>From</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>From</em>' reference isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>From</em>' reference.
	 * @see #setFrom(Page)
	 * @see webApplication.content.ContentPackage#getLink_From()
	 * @model required="true"
	 * @generated
	 */
	Page getFrom();

	/**
	 * Sets the value of the '{@link webApplication.content.Link#getFrom <em>From</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>From</em>' reference.
	 * @see #getFrom()
	 * @generated
	 */
	void setFrom(Page value);

	/**
	 * Returns the value of the '<em><b>To</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>To</em>' reference isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>To</em>' reference.
	 * @see #setTo(Page)
	 * @see webApplication.content.ContentPackage#getLink_To()
	 * @model required="true"
	 * @generated
	 */
	Page getTo();

	/**
	 * Sets the value of the '{@link webApplication.content.Link#getTo <em>To</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>To</em>' reference.
	 * @see #getTo()
	 * @generated
	 */
	void setTo(Page value);

} // Link
