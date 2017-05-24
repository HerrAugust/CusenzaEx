/**
 */
package webApplication.data;

import org.eclipse.emf.common.util.EList;

import webApplication.Named;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Entity</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link webApplication.data.Entity#getColumns <em>Columns</em>}</li>
 *   <li>{@link webApplication.data.Entity#getRelates <em>Relates</em>}</li>
 * </ul>
 *
 * @see webApplication.data.DataPackage#getEntity()
 * @model
 * @generated
 */
public interface Entity extends Named {
	/**
	 * Returns the value of the '<em><b>Columns</b></em>' containment reference list.
	 * The list contents are of type {@link webApplication.data.Column}.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Columns</em>' containment reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Columns</em>' containment reference list.
	 * @see webApplication.data.DataPackage#getEntity_Columns()
	 * @model containment="true" required="true"
	 * @generated
	 */
	EList<Column> getColumns();

	/**
	 * Returns the value of the '<em><b>Relates</b></em>' containment reference list.
	 * The list contents are of type {@link webApplication.data.RelatedEntity}.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Relates</em>' containment reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Relates</em>' containment reference list.
	 * @see webApplication.data.DataPackage#getEntity_Relates()
	 * @model containment="true"
	 * @generated
	 */
	EList<RelatedEntity> getRelates();

} // Entity
