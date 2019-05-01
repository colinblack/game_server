package ProtoBattleField {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class SkillOrShapeRush extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const HID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.SkillOrShapeRush.hid", "hid", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var hid:uint;

		/**
		 *  @private
		 */
		public static const SHAPE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.SkillOrShapeRush.shape", "shape", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var shape:uint;

		/**
		 *  @private
		 */
		public static const UID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.SkillOrShapeRush.uid", "uid", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var uid:uint;

		/**
		 *  @private
		 */
		public static const ID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.SkillOrShapeRush.id", "id", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var id:uint;

		/**
		 *  @private
		 */
		public static const EUID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.SkillOrShapeRush.euid", "euid", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var euid:uint;

		/**
		 *  @private
		 */
		public static const EID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.SkillOrShapeRush.eid", "eid", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var eid:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.hid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.shape);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.uid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.id);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.euid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.eid);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var hid$count:uint = 0;
			var shape$count:uint = 0;
			var uid$count:uint = 0;
			var id$count:uint = 0;
			var euid$count:uint = 0;
			var eid$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (hid$count != 0) {
						throw new flash.errors.IOError('Bad data format: SkillOrShapeRush.hid cannot be set twice.');
					}
					++hid$count;
					this.hid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (shape$count != 0) {
						throw new flash.errors.IOError('Bad data format: SkillOrShapeRush.shape cannot be set twice.');
					}
					++shape$count;
					this.shape = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (uid$count != 0) {
						throw new flash.errors.IOError('Bad data format: SkillOrShapeRush.uid cannot be set twice.');
					}
					++uid$count;
					this.uid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (id$count != 0) {
						throw new flash.errors.IOError('Bad data format: SkillOrShapeRush.id cannot be set twice.');
					}
					++id$count;
					this.id = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (euid$count != 0) {
						throw new flash.errors.IOError('Bad data format: SkillOrShapeRush.euid cannot be set twice.');
					}
					++euid$count;
					this.euid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (eid$count != 0) {
						throw new flash.errors.IOError('Bad data format: SkillOrShapeRush.eid cannot be set twice.');
					}
					++eid$count;
					this.eid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
