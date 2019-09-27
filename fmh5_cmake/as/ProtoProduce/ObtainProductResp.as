package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class ObtainProductResp
	{
		public static const PROTO:String = "ProtoProduce.ObtainProductResp";
		public var package_root:*;
		public  var message:*;
		public var isfull:Boolean;
		public var animal:AnimalCPP;
		public var commons:CommonItemsCPP;
		public function ObtainProductResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			isfull = undefined;
			animal = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.isfull = this.isfull;
			if(this.animal!= undefined)
			{
				serializeObj.animal = this.animal.serialize();
			}
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ObtainProductResp
		{
			isfull = undefined;
			animal = undefined;
			commons = undefined;
			this.isfull = msgObj.isfull;
			if(msgObj.hasOwnProperty("animal"))
			{
				this.animal = new AnimalCPP(package_root).unserialize(msgObj.animal);
			}
			if(msgObj.hasOwnProperty("commons"))
			{
				this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ObtainProductResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}