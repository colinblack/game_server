package User {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoActivity.GameAcitivityAllCPP;
	import User.Activity;
	import User.Base;
	import User.AccumulateCharge;
	import ProtoNotify.NotifyItemCPPAll;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class User extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const BASE:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.base", "base", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return User.Base; });

		public var base:User.Base;

		/**
		 *  @private
		 */
		public static const TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.User.ts", "ts", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var ts:uint;

		/**
		 *  @private
		 */
		public static const ACTIVITY:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.activity", "activity", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return User.Activity; });

		public var activity:User.Activity;

		/**
		 *  @private
		 */
		public static const NOTIFIES:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.notifies", "notifies", (4 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoNotify.NotifyItemCPPAll; });

		private var notifies$field:ProtoNotify.NotifyItemCPPAll;

		public function clearNotifies():void {
			notifies$field = null;
		}

		public function get hasNotifies():Boolean {
			return notifies$field != null;
		}

		public function set notifies(value:ProtoNotify.NotifyItemCPPAll):void {
			notifies$field = value;
		}

		public function get notifies():ProtoNotify.NotifyItemCPPAll {
			return notifies$field;
		}

		/**
		 *  @private
		 */
		public static const CHARGES:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.charges", "charges", (5 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return User.AccumulateCharge; });

		public var charges:User.AccumulateCharge;

		/**
		 *  @private
		 */
		public static const GAMEACTIVITY:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.User.gameactivity", "gameactivity", (6 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoActivity.GameAcitivityAllCPP; });

		public var gameactivity:ProtoActivity.GameAcitivityAllCPP;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.base);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.ts);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.activity);
			if (hasNotifies) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 4);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, notifies$field);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.charges);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.gameactivity);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var base$count:uint = 0;
			var ts$count:uint = 0;
			var activity$count:uint = 0;
			var notifies$count:uint = 0;
			var charges$count:uint = 0;
			var gameactivity$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (base$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.base cannot be set twice.');
					}
					++base$count;
					this.base = new User.Base();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.base);
					break;
				case 2:
					if (ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.ts cannot be set twice.');
					}
					++ts$count;
					this.ts = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (activity$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.activity cannot be set twice.');
					}
					++activity$count;
					this.activity = new User.Activity();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.activity);
					break;
				case 4:
					if (notifies$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.notifies cannot be set twice.');
					}
					++notifies$count;
					this.notifies = new ProtoNotify.NotifyItemCPPAll();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.notifies);
					break;
				case 5:
					if (charges$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.charges cannot be set twice.');
					}
					++charges$count;
					this.charges = new User.AccumulateCharge();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.charges);
					break;
				case 6:
					if (gameactivity$count != 0) {
						throw new flash.errors.IOError('Bad data format: User.gameactivity cannot be set twice.');
					}
					++gameactivity$count;
					this.gameactivity = new ProtoActivity.GameAcitivityAllCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.gameactivity);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
