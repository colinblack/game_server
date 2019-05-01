package ProtoComponent {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoComponent.ProduceComponentCPP;
	import ProtoComponent.ProductCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class OneKeyProduceResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const MATERIAL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoComponent.OneKeyProduceResp.material", "material", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var material:uint;

		/**
		 *  @private
		 */
		public static const PRODUCT:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoComponent.OneKeyProduceResp.product", "product", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoComponent.ProductCPP; });

		[ArrayElementType("ProtoComponent.ProductCPP")]
		public var product:Array = [];

		/**
		 *  @private
		 */
		public static const PRODUCE:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoComponent.OneKeyProduceResp.produce", "produce", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoComponent.ProduceComponentCPP; });

		public var produce:ProtoComponent.ProduceComponentCPP;

		/**
		 *  @private
		 */
		public static const STOPCODE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoComponent.OneKeyProduceResp.stopcode", "stopcode", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var stopcode:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.material);
			for (var product$index:uint = 0; product$index < this.product.length; ++product$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.product[product$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.produce);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.stopcode);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var material$count:uint = 0;
			var produce$count:uint = 0;
			var stopcode$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (material$count != 0) {
						throw new flash.errors.IOError('Bad data format: OneKeyProduceResp.material cannot be set twice.');
					}
					++material$count;
					this.material = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					this.product.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoComponent.ProductCPP()));
					break;
				case 3:
					if (produce$count != 0) {
						throw new flash.errors.IOError('Bad data format: OneKeyProduceResp.produce cannot be set twice.');
					}
					++produce$count;
					this.produce = new ProtoComponent.ProduceComponentCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.produce);
					break;
				case 4:
					if (stopcode$count != 0) {
						throw new flash.errors.IOError('Bad data format: OneKeyProduceResp.stopcode cannot be set twice.');
					}
					++stopcode$count;
					this.stopcode = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
