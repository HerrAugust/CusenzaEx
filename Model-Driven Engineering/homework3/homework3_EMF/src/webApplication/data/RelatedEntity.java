/**
 */
package webApplication.data;

import webApplication.Named;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Related Entity</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link webApplication.data.RelatedEntity#getRelatesTo <em>Relates To</em>}</li>
 * </ul>
 *
 * @see webApplication.data.DataPackage#getRelatedEntity()
 * @model
 * @generated
 */
public interface RelatedEntity extends Named {
	/**
	 * Returns the value of the '<em><b>Relates To</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Relates To</em>' reference isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Relates To</em>' reference.
	 * @see #setRelatesTo(Entity)
	 * @see webApplication.data.DataPackage#getRelatedEntity_RelatesTo()
	 * @model required="true"
	 * @generated
	 */
	Entity getRelatesTo();

	/**
	 * Sets the value of the '{@link webApplication.data.RelatedEntity#getRelatesTo <em>Relates To</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Relates To</em>' reference.
	 * @see #getRelatesTo()
	 * @generated
	 */
	void setRelatesTo(Entity value);

} // RelatedEntity
