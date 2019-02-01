package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCSGetPartTimeClubReq
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoCSGetPartTimeClubReq";
		public var package_root:*;
		public  var message:*;
		public var myUid:int;
		public var othUid:int;
		public var clubInfo:Vector.<ProtoPartimeInfo>;
		public function ProtoCSGetPartTimeClubReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			myUid = undefined;
			othUid = undefined;
			clubInfo = new Vector.<ProtoPartimeInfo>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myUid = this.myUid;
			serializeObj.othUid = this.othUid;
			serializeObj.clubInfo = [];
			for(var i:int = 0;i < this.clubInfo.length;i++)
			{
				serializeObj.clubInfo.push(this.clubInfo[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSGetPartTimeClubReq
		{
			myUid = undefined;
			othUid = undefined;
			clubInfo = new Vector.<ProtoPartimeInfo>();
			this.myUid = msgObj.myUid;
			this.othUid = msgObj.othUid;
			for(var i:int = 0;i < msgObj.clubInfo.length;i++)
			{
				this.clubInfo.push(new ProtoPartimeInfo(package_root).unserialize(msgObj.clubInfo[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoCSGetPartTimeClubReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}