package User {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import User.AccumulateCharge;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class PushAccumulateChangeReq extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const CHANGE_ACCCHARGE:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.PushAccumulateChangeReq.change_acccharge", "changeAcccharge", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return User.AccumulateCharge; });

		public var changeAcccharge:User.AccumulateCharge;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.changeAcccharge);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var change_acccharge$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (change_acccharge$count != 0) {
						throw new flash.errors.IOError('Bad data format: PushAccumulateChangeReq.changeAcccharge cannot be set twice.');
					}
					++change_acccharge$count;
					this.changeAcccharge = new User.AccumulateCharge();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.changeAcccharge);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
