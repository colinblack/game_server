package User {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import flash.utils.ByteArray;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class Base extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const UID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.uid", "uid", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var uid:uint;

		/**
		 *  @private
		 */
		public static const REGISTER_PLATFORM:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.register_platform", "registerPlatform", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var registerPlatform:uint;

		/**
		 *  @private
		 */
		public static const REGISTER_TIME:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.register_time", "registerTime", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var registerTime:uint;

		/**
		 *  @private
		 */
		public static const LAST_LOGIN_PLATFORM:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.last_login_platform", "lastLoginPlatform", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var lastLoginPlatform:uint;

		/**
		 *  @private
		 */
		public static const LAST_LOGIN_TIME:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.last_login_time", "lastLoginTime", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var lastLoginTime:uint;

		/**
		 *  @private
		 */
		public static const LOGIN_TIMES:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.login_times", "loginTimes", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var loginTimes:uint;

		/**
		 *  @private
		 */
		public static const LOGIN_DAYS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.login_days", "loginDays", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		public var loginDays:uint;

		/**
		 *  @private
		 */
		public static const LAST_ACTIVE_TIME:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.last_active_time", "lastActiveTime", (8 << 3) | com.netease.protobuf.WireType.VARINT);

		public var lastActiveTime:uint;

		/**
		 *  @private
		 */
		public static const LAST_OFF_TIME:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.last_off_time", "lastOffTime", (9 << 3) | com.netease.protobuf.WireType.VARINT);

		public var lastOffTime:uint;

		/**
		 *  @private
		 */
		public static const FORBID_TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.forbid_ts", "forbidTs", (10 << 3) | com.netease.protobuf.WireType.VARINT);

		public var forbidTs:uint;

		/**
		 *  @private
		 */
		public static const FORBID_REASON:FieldDescriptor_TYPE_BYTES = new FieldDescriptor_TYPE_BYTES("User.Base.forbid_reason", "forbidReason", (11 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var forbidReason:flash.utils.ByteArray;

		/**
		 *  @private
		 */
		public static const TUTORIAL_STAGE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.tutorial_stage", "tutorialStage", (12 << 3) | com.netease.protobuf.WireType.VARINT);

		public var tutorialStage:uint;

		/**
		 *  @private
		 */
		public static const NAME:FieldDescriptor_TYPE_BYTES = new FieldDescriptor_TYPE_BYTES("User.Base.name", "name", (13 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var name:flash.utils.ByteArray;

		/**
		 *  @private
		 */
		public static const FIG:FieldDescriptor_TYPE_BYTES = new FieldDescriptor_TYPE_BYTES("User.Base.fig", "fig", (14 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var fig:flash.utils.ByteArray;

		/**
		 *  @private
		 */
		public static const EXP:FieldDescriptor_TYPE_UINT64 = new FieldDescriptor_TYPE_UINT64("User.Base.exp", "exp", (15 << 3) | com.netease.protobuf.WireType.VARINT);

		public var exp:UInt64;

		/**
		 *  @private
		 */
		public static const LEVEL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.level", "level", (16 << 3) | com.netease.protobuf.WireType.VARINT);

		public var level:uint;

		/**
		 *  @private
		 */
		public static const ACCCHARGE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.acccharge", "acccharge", (17 << 3) | com.netease.protobuf.WireType.VARINT);

		public var acccharge:uint;

		/**
		 *  @private
		 */
		public static const VIPLEVEL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.viplevel", "viplevel", (18 << 3) | com.netease.protobuf.WireType.VARINT);

		public var viplevel:uint;

		/**
		 *  @private
		 */
		public static const CASH:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.cash", "cash", (19 << 3) | com.netease.protobuf.WireType.VARINT);

		public var cash:uint;

		/**
		 *  @private
		 */
		public static const COIN:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.coin", "coin", (20 << 3) | com.netease.protobuf.WireType.VARINT);

		public var coin:uint;

		/**
		 *  @private
		 */
		public static const FIRST_RECHARGE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.first_recharge", "firstRecharge", (21 << 3) | com.netease.protobuf.WireType.VARINT);

		public var firstRecharge:uint;

		/**
		 *  @private
		 */
		public static const ALLIANCE_ID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Base.alliance_id", "allianceId", (22 << 3) | com.netease.protobuf.WireType.VARINT);

		public var allianceId:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.uid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.registerPlatform);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.registerTime);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.lastLoginPlatform);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.lastLoginTime);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.loginTimes);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.loginDays);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 8);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.lastActiveTime);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 9);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.lastOffTime);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 10);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.forbidTs);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 11);
			com.netease.protobuf.WriteUtils.write_TYPE_BYTES(output, this.forbidReason);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 12);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.tutorialStage);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 13);
			com.netease.protobuf.WriteUtils.write_TYPE_BYTES(output, this.name);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 14);
			com.netease.protobuf.WriteUtils.write_TYPE_BYTES(output, this.fig);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 15);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT64(output, this.exp);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 16);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.level);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 17);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.acccharge);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 18);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.viplevel);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 19);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.cash);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 20);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.coin);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 21);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.firstRecharge);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 22);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.allianceId);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var uid$count:uint = 0;
			var register_platform$count:uint = 0;
			var register_time$count:uint = 0;
			var last_login_platform$count:uint = 0;
			var last_login_time$count:uint = 0;
			var login_times$count:uint = 0;
			var login_days$count:uint = 0;
			var last_active_time$count:uint = 0;
			var last_off_time$count:uint = 0;
			var forbid_ts$count:uint = 0;
			var forbid_reason$count:uint = 0;
			var tutorial_stage$count:uint = 0;
			var name$count:uint = 0;
			var fig$count:uint = 0;
			var exp$count:uint = 0;
			var level$count:uint = 0;
			var acccharge$count:uint = 0;
			var viplevel$count:uint = 0;
			var cash$count:uint = 0;
			var coin$count:uint = 0;
			var first_recharge$count:uint = 0;
			var alliance_id$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (uid$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.uid cannot be set twice.');
					}
					++uid$count;
					this.uid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (register_platform$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.registerPlatform cannot be set twice.');
					}
					++register_platform$count;
					this.registerPlatform = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (register_time$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.registerTime cannot be set twice.');
					}
					++register_time$count;
					this.registerTime = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (last_login_platform$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.lastLoginPlatform cannot be set twice.');
					}
					++last_login_platform$count;
					this.lastLoginPlatform = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (last_login_time$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.lastLoginTime cannot be set twice.');
					}
					++last_login_time$count;
					this.lastLoginTime = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (login_times$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.loginTimes cannot be set twice.');
					}
					++login_times$count;
					this.loginTimes = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 7:
					if (login_days$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.loginDays cannot be set twice.');
					}
					++login_days$count;
					this.loginDays = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 8:
					if (last_active_time$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.lastActiveTime cannot be set twice.');
					}
					++last_active_time$count;
					this.lastActiveTime = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 9:
					if (last_off_time$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.lastOffTime cannot be set twice.');
					}
					++last_off_time$count;
					this.lastOffTime = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 10:
					if (forbid_ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.forbidTs cannot be set twice.');
					}
					++forbid_ts$count;
					this.forbidTs = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 11:
					if (forbid_reason$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.forbidReason cannot be set twice.');
					}
					++forbid_reason$count;
					this.forbidReason = com.netease.protobuf.ReadUtils.read_TYPE_BYTES(input);
					break;
				case 12:
					if (tutorial_stage$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.tutorialStage cannot be set twice.');
					}
					++tutorial_stage$count;
					this.tutorialStage = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 13:
					if (name$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.name cannot be set twice.');
					}
					++name$count;
					this.name = com.netease.protobuf.ReadUtils.read_TYPE_BYTES(input);
					break;
				case 14:
					if (fig$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.fig cannot be set twice.');
					}
					++fig$count;
					this.fig = com.netease.protobuf.ReadUtils.read_TYPE_BYTES(input);
					break;
				case 15:
					if (exp$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.exp cannot be set twice.');
					}
					++exp$count;
					this.exp = com.netease.protobuf.ReadUtils.read_TYPE_UINT64(input);
					break;
				case 16:
					if (level$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.level cannot be set twice.');
					}
					++level$count;
					this.level = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 17:
					if (acccharge$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.acccharge cannot be set twice.');
					}
					++acccharge$count;
					this.acccharge = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 18:
					if (viplevel$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.viplevel cannot be set twice.');
					}
					++viplevel$count;
					this.viplevel = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 19:
					if (cash$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.cash cannot be set twice.');
					}
					++cash$count;
					this.cash = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 20:
					if (coin$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.coin cannot be set twice.');
					}
					++coin$count;
					this.coin = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 21:
					if (first_recharge$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.firstRecharge cannot be set twice.');
					}
					++first_recharge$count;
					this.firstRecharge = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 22:
					if (alliance_id$count != 0) {
						throw new flash.errors.IOError('Bad data format: Base.allianceId cannot be set twice.');
					}
					++alliance_id$count;
					this.allianceId = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
