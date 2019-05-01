package ProtoMine {
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
	public dynamic final class MineItem extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const UID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMine.MineItem.uid", "uid", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var uid:uint;

		/**
		 *  @private
		 */
		public static const LEVEL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMine.MineItem.level", "level", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var level:uint;

		/**
		 *  @private
		 */
		public static const DONATE_CNT:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMine.MineItem.donate_cnt", "donateCnt", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var donateCnt:uint;

		/**
		 *  @private
		 */
		public static const IS_DONATE:FieldDescriptor_TYPE_BOOL = new FieldDescriptor_TYPE_BOOL("ProtoMine.MineItem.is_donate", "isDonate", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var isDonate:Boolean;

		/**
		 *  @private
		 */
		public static const NAME:FieldDescriptor_TYPE_BYTES = new FieldDescriptor_TYPE_BYTES("ProtoMine.MineItem.name", "name", (5 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var name:flash.utils.ByteArray;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.uid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.level);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.donateCnt);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_BOOL(output, this.isDonate);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_BYTES(output, this.name);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var uid$count:uint = 0;
			var level$count:uint = 0;
			var donate_cnt$count:uint = 0;
			var is_donate$count:uint = 0;
			var name$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (uid$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineItem.uid cannot be set twice.');
					}
					++uid$count;
					this.uid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (level$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineItem.level cannot be set twice.');
					}
					++level$count;
					this.level = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (donate_cnt$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineItem.donateCnt cannot be set twice.');
					}
					++donate_cnt$count;
					this.donateCnt = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (is_donate$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineItem.isDonate cannot be set twice.');
					}
					++is_donate$count;
					this.isDonate = com.netease.protobuf.ReadUtils.read_TYPE_BOOL(input);
					break;
				case 5:
					if (name$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineItem.name cannot be set twice.');
					}
					++name$count;
					this.name = com.netease.protobuf.ReadUtils.read_TYPE_BYTES(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
