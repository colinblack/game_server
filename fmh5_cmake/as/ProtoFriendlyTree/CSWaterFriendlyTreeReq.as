package com.sanguo.game.server.connectlogic.common.message.ProtoFriendlyTree
{
	import laya.utils.Byte;
	public class CSWaterFriendlyTreeReq
	{
		public static const PROTO:String = "ProtoFriendlyTree.CSWaterFriendlyTreeReq";
		public var package_root:*;
		public  var message:*;
		public var myuid:int;
		public var myname:Byte;
		public var myhead:Byte;
		public var othuid:int;
		public function CSWaterFriendlyTreeReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			myuid = undefined;
			myname = undefined;
			myhead = undefined;
			othuid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myuid = this.myuid;
			this.myname.pos = 0;
			this.myhead.pos = 0;
			serializeObj.othuid = this.othuid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):CSWaterFriendlyTreeReq
		{
			myuid = undefined;
			myname = undefined;
			myhead = undefined;
			othuid = undefined;
			this.myuid = msgObj.myuid;
			this.myname = new Byte();
			this.myname.writeArrayBuffer(msgObj.myname);
			this.myname.pos = 0;
			this.myhead = new Byte();
			this.myhead.writeArrayBuffer(msgObj.myhead);
			this.myhead.pos = 0;
			this.othuid = msgObj.othuid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CSWaterFriendlyTreeReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}