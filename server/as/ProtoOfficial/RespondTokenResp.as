package ProtoOfficial {
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
	public dynamic final class RespondTokenResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const HERO_IDS:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("ProtoOfficial.RespondTokenResp.hero_ids", "heroIds", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var heroIds:Array = [];

		/**
		 *  @private
		 */
		public static const TOKEN_TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoOfficial.RespondTokenResp.token_ts", "tokenTs", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var tokenTs:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			for (var heroIds$index:uint = 0; heroIds$index < this.heroIds.length; ++heroIds$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.heroIds[heroIds$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.tokenTs);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var token_ts$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.heroIds);
						break;
					}
					this.heroIds.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				case 2:
					if (token_ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: RespondTokenResp.tokenTs cannot be set twice.');
					}
					++token_ts$count;
					this.tokenTs = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
