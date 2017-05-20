/**
 */
package webApplication.data.impl;

import org.eclipse.emf.common.notify.Notification;

import org.eclipse.emf.ecore.EClass;

import org.eclipse.emf.ecore.impl.ENotificationImpl;

import webApplication.data.Column;
import webApplication.data.ColumnType;
import webApplication.data.DataPackage;

import webApplication.impl.NamedImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Column</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link webApplication.data.impl.ColumnImpl#getType <em>Type</em>}</li>
 *   <li>{@link webApplication.data.impl.ColumnImpl#getLenght <em>Lenght</em>}</li>
 *   <li>{@link webApplication.data.impl.ColumnImpl#isPK <em>PK</em>}</li>
 * </ul>
 *
 * @generated
 */
public class ColumnImpl extends NamedImpl implements Column {
	/**
	 * The default value of the '{@link #getType() <em>Type</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getType()
	 * @generated
	 * @ordered
	 */
	protected static final ColumnType TYPE_EDEFAULT = ColumnType.STRING;

	/**
	 * The cached value of the '{@link #getType() <em>Type</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getType()
	 * @generated
	 * @ordered
	 */
	protected ColumnType type = TYPE_EDEFAULT;

	/**
	 * The default value of the '{@link #getLenght() <em>Lenght</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getLenght()
	 * @generated
	 * @ordered
	 */
	protected static final int LENGHT_EDEFAULT = 0;

	/**
	 * The cached value of the '{@link #getLenght() <em>Lenght</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getLenght()
	 * @generated
	 * @ordered
	 */
	protected int lenght = LENGHT_EDEFAULT;

	/**
	 * The default value of the '{@link #isPK() <em>PK</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #isPK()
	 * @generated
	 * @ordered
	 */
	protected static final boolean PK_EDEFAULT = false;

	/**
	 * The cached value of the '{@link #isPK() <em>PK</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #isPK()
	 * @generated
	 * @ordered
	 */
	protected boolean pk = PK_EDEFAULT;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected ColumnImpl() {
		super();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	protected EClass eStaticClass() {
		return DataPackage.Literals.COLUMN;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public ColumnType getType() {
		return type;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setType(ColumnType newType) {
		ColumnType oldType = type;
		type = newType == null ? TYPE_EDEFAULT : newType;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, DataPackage.COLUMN__TYPE, oldType, type));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public int getLenght() {
		return lenght;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setLenght(int newLenght) {
		int oldLenght = lenght;
		lenght = newLenght;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, DataPackage.COLUMN__LENGHT, oldLenght, lenght));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public boolean isPK() {
		return pk;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setPK(boolean newPK) {
		boolean oldPK = pk;
		pk = newPK;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, DataPackage.COLUMN__PK, oldPK, pk));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public Object eGet(int featureID, boolean resolve, boolean coreType) {
		switch (featureID) {
			case DataPackage.COLUMN__TYPE:
				return getType();
			case DataPackage.COLUMN__LENGHT:
				return getLenght();
			case DataPackage.COLUMN__PK:
				return isPK();
		}
		return super.eGet(featureID, resolve, coreType);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public void eSet(int featureID, Object newValue) {
		switch (featureID) {
			case DataPackage.COLUMN__TYPE:
				setType((ColumnType)newValue);
				return;
			case DataPackage.COLUMN__LENGHT:
				setLenght((Integer)newValue);
				return;
			case DataPackage.COLUMN__PK:
				setPK((Boolean)newValue);
				return;
		}
		super.eSet(featureID, newValue);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public void eUnset(int featureID) {
		switch (featureID) {
			case DataPackage.COLUMN__TYPE:
				setType(TYPE_EDEFAULT);
				return;
			case DataPackage.COLUMN__LENGHT:
				setLenght(LENGHT_EDEFAULT);
				return;
			case DataPackage.COLUMN__PK:
				setPK(PK_EDEFAULT);
				return;
		}
		super.eUnset(featureID);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public boolean eIsSet(int featureID) {
		switch (featureID) {
			case DataPackage.COLUMN__TYPE:
				return type != TYPE_EDEFAULT;
			case DataPackage.COLUMN__LENGHT:
				return lenght != LENGHT_EDEFAULT;
			case DataPackage.COLUMN__PK:
				return pk != PK_EDEFAULT;
		}
		return super.eIsSet(featureID);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public String toString() {
		if (eIsProxy()) return super.toString();

		StringBuffer result = new StringBuffer(super.toString());
		result.append(" (type: ");
		result.append(type);
		result.append(", lenght: ");
		result.append(lenght);
		result.append(", PK: ");
		result.append(pk);
		result.append(')');
		return result.toString();
	}

} //ColumnImpl
