package com.sanguo.game.server.connectlogic.common.message.ProtoActivity
{
	import laya.utils.Byte;
	public class GameAcitivityStatusReq
	{
		public static const PROTO:String = "ProtoActivity.GameAcitivityStatusReq";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public function GameAcitivityStatusReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			return serializeObj;
		}
		public function unserialize(msgObj:*):GameAcitivityStatusReq
		{
			id = undefined;
			this.id = msgObj.id;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GameAcitivityStatusReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}