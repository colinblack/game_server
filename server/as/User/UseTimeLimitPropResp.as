package User {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import User.TimeLimtPropItem;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class UseTimeLimitPropResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const EQUD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.UseTimeLimitPropResp.equd", "equd", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var equd:uint;

		/**
		 *  @private
		 */
		public static const COUNT:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.UseTimeLimitPropResp.count", "count", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var count:uint;

		/**
		 *  @private
		 */
		public static const ITEM:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.UseTimeLimitPropResp.item", "item", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return User.TimeLimtPropItem; });

		public var item:User.TimeLimtPropItem;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.equd);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.count);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.item);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var equd$count:uint = 0;
			var count$count:uint = 0;
			var item$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (equd$count != 0) {
						throw new flash.errors.IOError('Bad data format: UseTimeLimitPropResp.equd cannot be set twice.');
					}
					++equd$count;
					this.equd = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (count$count != 0) {
						throw new flash.errors.IOError('Bad data format: UseTimeLimitPropResp.count cannot be set twice.');
					}
					++count$count;
					this.count = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (item$count != 0) {
						throw new flash.errors.IOError('Bad data format: UseTimeLimitPropResp.item cannot be set twice.');
					}
					++item$count;
					this.item = new User.TimeLimtPropItem();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.item);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
