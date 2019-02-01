package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoGetOtherIncomeReq
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoGetOtherIncomeReq";
		public var package_root:*;
		public  var message:*;
		public var othUid:int;
		public var heroId:int;
		public var slot:int;
		public function ProtoGetOtherIncomeReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			othUid = undefined;
			heroId = undefined;
			slot = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.othUid = this.othUid;
			serializeObj.heroId = this.heroId;
			serializeObj.slot = this.slot;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoGetOtherIncomeReq
		{
			othUid = undefined;
			heroId = undefined;
			slot = undefined;
			this.othUid = msgObj.othUid;
			this.heroId = msgObj.heroId;
			this.slot = msgObj.slot;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoGetOtherIncomeReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}