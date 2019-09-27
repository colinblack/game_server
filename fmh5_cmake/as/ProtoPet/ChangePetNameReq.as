package com.sanguo.game.server.connectlogic.common.message.ProtoPet
{
	import laya.utils.Byte;
	public class ChangePetNameReq
	{
		public static const PROTO:String = "ProtoPet.ChangePetNameReq";
		public var package_root:*;
		public  var message:*;
		public var petid:int;
		public var name:Byte;
		public function ChangePetNameReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			petid = undefined;
			name = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.petid = this.petid;
			this.name.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ChangePetNameReq
		{
			petid = undefined;
			name = undefined;
			this.petid = msgObj.petid;
			this.name = new Byte();
			this.name.writeArrayBuffer(msgObj.name);
			this.name.pos = 0;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ChangePetNameReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}