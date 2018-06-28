package User {
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
	public dynamic final class ActivityItem extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const ID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.ActivityItem.id", "id", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var id:uint;

		/**
		 *  @private
		 */
		public static const BTS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.ActivityItem.bts", "bts", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var bts:uint;

		/**
		 *  @private
		 */
		public static const ETS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.ActivityItem.ets", "ets", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var ets:uint;

		/**
		 *  @private
		 */
		public static const VER:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.ActivityItem.ver", "ver", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var ver:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.id);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.bts);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.ets);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.ver);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var id$count:uint = 0;
			var bts$count:uint = 0;
			var ets$count:uint = 0;
			var ver$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (id$count != 0) {
						throw new flash.errors.IOError('Bad data format: ActivityItem.id cannot be set twice.');
					}
					++id$count;
					this.id = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (bts$count != 0) {
						throw new flash.errors.IOError('Bad data format: ActivityItem.bts cannot be set twice.');
					}
					++bts$count;
					this.bts = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (ets$count != 0) {
						throw new flash.errors.IOError('Bad data format: ActivityItem.ets cannot be set twice.');
					}
					++ets$count;
					this.ets = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (ver$count != 0) {
						throw new flash.errors.IOError('Bad data format: ActivityItem.ver cannot be set twice.');
					}
					++ver$count;
					this.ver = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
