package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoGetMartialClubResp
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoGetMartialClubResp";
		public var package_root:*;
		public  var message:*;
		public var group:Vector.<MartialClubGroup>;
		public function ProtoGetMartialClubResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			group = new Vector.<MartialClubGroup>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.group = [];
			for(var i:int = 0;i < this.group.length;i++)
			{
				serializeObj.group.push(this.group[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoGetMartialClubResp
		{
			group = new Vector.<MartialClubGroup>();
			for(var i:int = 0;i < msgObj.group.length;i++)
			{
				this.group.push(new MartialClubGroup(package_root).unserialize(msgObj.group[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoGetMartialClubResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}